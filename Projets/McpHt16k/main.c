#include<stdio.h>
#include<errno.h>
#include<wiringPi.h>
#include<wiringPiI2C.h>
#include"fonctions.h"
#include<pthread.h>
#include"main.h"

#define IODIR   0x00 // GPIO en OUTPUT 0 ou INPUT 1.
#define GPIO	0x09 // Registre des GPIO

#define BTNG	0x80 // Valeur hexa du bouton gauche.
#define BTND	0x40 // Valeur hexa du bouton droit.
#define LEDG	0x07 // Allumer les leds a gauche
#define LEDD	0x38 // Allumer les leds a droite
#define LEDALL	0x3F // Allumer toutes les leds
#define LEDNOT	0x00 // Eteindre toutes les leds.

struct arg_jeux
{
int Mcp ;
int J ;
int *EtatLed ;
int Ht16k ;
};

void* Jeux(void* data)
{
 struct arg_jeux *e = data ;
 int Mcp = e->Mcp ;
 int J = e->J ;
 int *EtatLed = e->EtatLed ;
 int Ht16k = e->Ht16k ;
 
 
 
 if (J == 0)
 {

 wiringPiI2CWriteReg8 (Mcp, GPIO, LEDNOT) ;
   *EtatLed = LEDNOT ;
 }

 if (J == 1)
 {
   wiringPiI2CWriteReg8 (Mcp, GPIO, LEDALL) ;
   *EtatLed = LEDALL ;
 }

 if  (J == 2)
 {
  wiringPiI2CWrite (Ht16k, 0x81) ;

   while (1)
   {
      wiringPiI2CWriteReg8 (Mcp, GPIO, LEDNOT) ;
      *EtatLed = LEDNOT ;
      delay (500) ;
      wiringPiI2CWriteReg8 (Mcp, GPIO, LEDALL) ;
      *EtatLed = LEDALL ;
      delay (500) ;
    
	}
 }

 if  (J == 3)
 {
  wiringPiI2CWrite (Ht16k, 0x81) ;

   while (1)
    {
      wiringPiI2CWriteReg8 (Mcp, GPIO, LEDG) ;
      *EtatLed = LEDG ;
      delay (500) ;
      wiringPiI2CWriteReg8 (Mcp, GPIO, LEDD) ;
      *EtatLed = LEDD ;
      delay (500) ;
    }
 }

 if  (J == 4)
 {
   wiringPiI2CWrite (Ht16k, 0x81) ;
 
   while (1)
    {
      int b;
	  int LED[7] = {0x00, 0x01, 0x02, 0x04, 0x08, 0x10, 0x20};

      for (b = 0 ; b < 7 ; b++)
      {
        wiringPiI2CWriteReg8 (Mcp, GPIO, LED[b]) ;
        *EtatLed = LED[b] ;
	    delay (500);
      }	
 	 
	  for (b = 6 ; b > 0 ; b--)
      {
        wiringPiI2CWriteReg8 (Mcp, GPIO, LED[b]) ;
        *EtatLed = LED[b] ;
	    delay (500);
      }
	    
    }
 }

}

void BtnAppuiLong (int Mcp, int *EtatLed)
{
 while ((wiringPiI2CReadReg8 (Mcp, GPIO) - *EtatLed) == BTNG)
  {
    delay (20);
  }

 while ((wiringPiI2CReadReg8 (Mcp, GPIO) - *EtatLed) == BTND)
  {
    delay (20) ;
  }
}

int main (void) // Fonction principale
{
  int Ht16k, Mcp, EtatLed, EtatBTN ; // Declaration des variables.
  int i = 1 ;
  pthread_t Thread_Jeux;
  
  Ht16k = wiringPiI2CSetup (0x70) ;

 if ((Mcp = wiringPiI2CSetup (0x20)) == -1)
 {
   fprintf (stderr, "Mcp: impossible d'initialiser l'I2C: %s\n", strerror (errno)) ; return 1 ; // Si impossible a initialiser.
 }

 
  wiringPiI2CWriteReg8 (Mcp, IODIR, 0xC0) ; // Toutes les broches en OUTPUT sauf broches 6 et 7 en input.
  wiringPiI2CWriteReg8 (Mcp, GPIO, LEDNOT) ; // Eteindre toutes les LEDs
  wiringPiI2CWrite (Ht16k, 0x21) ;
  wiringPiI2CWrite (Ht16k, 0x81) ;
  Afficher (Ht16k, 0) ;

  EtatLed = LEDNOT ; // Par defaut les LEDs sont eteintes.

  struct arg_jeux TypeDeJeu = {Mcp, 0, &EtatLed, Ht16k} ;
  
 for (;;)
 {
   debut: //Etiquette goto je ne sai pas faire autrement..
   wiringPiI2CWrite (Ht16k, 0x81) ;
   EtatBTN = (wiringPiI2CReadReg8 (Mcp, GPIO) - EtatLed) ;

   if (EtatBTN == BTNG) // Si bouton gauche presser alors...
   {
     delay (200); // On attend 10ms puis on fait une relecture pour etre sur que ce n'est pas un parasite
       if ((wiringPiI2CReadReg8 (Mcp, GPIO) - EtatLed) == BTNG) // Si bouton gauche presser..
       {
         wiringPiI2CWrite (Ht16k, 0x83);
         BtnAppuiLong (Mcp, &EtatLed) ;

          while ((wiringPiI2CReadReg8 (Mcp, GPIO) - EtatLed) != BTND)
           {
             delay (20) ;

			 if ((wiringPiI2CReadReg8 (Mcp, GPIO) - EtatLed) == BTNG)
             {
               Afficher (Ht16k, i) ;
               i++ ;
                if (i == 10) {i =0 ;}
                BtnAppuiLong (Mcp, &EtatLed) ;
				TypeDeJeu.J = (i-1) ;
				TypeDeJeu.EtatLed = &EtatLed ;
				}

           }

	    pthread_cancel(Thread_Jeux);	
		pthread_create (&Thread_Jeux, NULL, Jeux, &TypeDeJeu);
        printf("coucou\n") ;

       }
   }
  delay (100); // Vitesse de la boucle
 }
return 0 ;
}
