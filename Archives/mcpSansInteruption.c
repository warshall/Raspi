#include<stdio.h>
#include<errno.h>
#include<wiringPi.h>
#include<wiringPiI2C.h>

#define IODIR	0x00 // GPIO en OUTPUT 0 ou INPUT 1.
#define GPIO	0x09 // Registre des GPIO

#define BTNG	0x80 // Valeur hexa du bouton gauche.
#define BTND	0x40 // Valeur hexa du bouton droit.
#define LEDG	0x07 // Allumer les leds a gauche
#define LEDD	0x38 // Allumer les leds a droite
#define LEDALL	0x3F // Allumer toutes les leds
#define LEDNOT	0x00 // Eteindre toutes les leds.

int EtatLed, Mcp ;


int BtnAppuiLong (void)
{

 while ((wiringPiI2CReadReg8 (Mcp, GPIO) - EtatLed) == BTNG)
      {
       delay (20);
      }

 while ((wiringPiI2CReadReg8 (Mcp, GPIO) - EtatLed) == BTND)
      {
       delay (20) ;
      }

return 0 ;

}

int main (void) // Fonction principale
{

 int EtatLedG, EtatLedD, EtatBTN ; // Declaration des variables.


if ((Mcp = wiringPiI2CSetup (0x20)) == -1)
{
  fprintf (stderr, "Mcp: impossible d'initialiser l'I2C: %s\n", strerror (errno)) ; return 1 ; // Si impossible a initialiser.
}


 EtatLedG = 0 ; // Initialisation des variables
 EtatLedD = 0 ;

 wiringPiI2CWriteReg8 (Mcp, IODIR, 0xC0) ; // Toutes les broches en OUTPUT sauf broches 6 et 7 en input.
 wiringPiI2CWriteReg8 (Mcp, GPIO, LEDNOT) ; // Eteindre toutes les LEDs
 EtatLed = LEDNOT ; // Par defaut les LEDs sont eteintes.


for (;;)
{

debut: //Etiquette goto je ne sai pas faire autrement..

EtatBTN = (wiringPiI2CReadReg8 (Mcp, GPIO) - EtatLed) ;


   if (EtatBTN == BTNG) // Si bouton gauche presser alors...
   {
     delay (10); // On attend 10ms puis on fait une relecture pour etre sur que ce n'est pas un parasite
       if ((wiringPiI2CReadReg8 (Mcp, GPIO) - EtatLed) == BTNG) // Si bouton gauche presser..
       {
         if (EtatLedG == 0 && EtatLedD == 0) // Si led gauche et droite sont eteintent
         {
           printf("Lumiere gauche allumer !\n") ;
           wiringPiI2CWriteReg8 (Mcp, GPIO, LEDG) ; // Allumage des LED a gauche
           delay (100); // Attendre 100ms
           EtatLed = LEDG ;
           EtatLedG = 1 ; // On specifi que les Led a gauche sont allumer.
           BtnAppuiLong () ;
           goto debut ; // On revient au debut de la boucle sinon execution de la condition suivante.
         }
         if (EtatLedG == 1 && EtatLedD == 0) // Si led gauche allumer et led droite eteintent
         {
           printf("Lumiere gauche et droite eteintent !\n") ;
           wiringPiI2CWriteReg8 (Mcp, GPIO, LEDNOT) ; // On eteind tout.
           delay (100) ;
           EtatLed = LEDNOT ;
           EtatLedG = 0 ;
           BtnAppuiLong () ;
           goto debut ;
         }
         if (EtatLedG == 0 && EtatLedD == 1) // Si Led gauche eteintent et led droite allumer
         {
           printf("Lumiere gauche et droite allumer !\n") ;
           wiringPiI2CWriteReg8 (Mcp, GPIO, LEDALL) ; // On allume tout.
           delay (100);
           EtatLed = LEDALL ;
           EtatLedG = 1 ;
           BtnAppuiLong () ;
           goto debut ;
         }
         if (EtatLedG == 1 && EtatLedD == 1) // Si Led gauche allumer et Led droite allumer
         {
           printf("Lumiere gauche eteint et droite allumer !\n") ;
           wiringPiI2CWriteReg8 (Mcp, GPIO, LEDD) ; // On allume que les leds droite.
           delay (100) ;
           EtatLed = LEDD ;
           EtatLedG = 0 ;
           BtnAppuiLong () ;
           goto debut ;
         }
       }
   }


   if (EtatBTN == BTND) // Si bouton droit presser alors...
   {
     delay (10); // On attend 10ms puis on fait une relecture pour etre sur que ce n'est pas un parasite
       if ((wiringPiI2CReadReg8 (Mcp, GPIO) - EtatLed) == BTND) // Si bouton droit presser..
       {
         if (EtatLedG == 0 && EtatLedD == 0) // Si les leds gauche et droite sont eteintent
         {
           printf("Lumiere droite allumer !\n") ;
           wiringPiI2CWriteReg8 (Mcp, GPIO, LEDD) ; // On allume que les leds droite
           delay (100);
           EtatLed = LEDD ;
           EtatLedD = 1 ;
           BtnAppuiLong () ;
           goto debut ;
         }
         if (EtatLedG == 1 && EtatLedD == 0) // Si Led gauche allumer et Led droite eteintent
         {
           printf("Lumiere gauche et droite allumer !\n") ;
           wiringPiI2CWriteReg8 (Mcp, GPIO, LEDALL) ; // On allume toutes les leds
           delay (100) ;
           EtatLed = LEDALL ;
           EtatLedD = 1 ;
           BtnAppuiLong () ;
           goto debut ;
         }
         if (EtatLedG == 0 && EtatLedD == 1) // Si Led gauche eteintent et droite allumer
         {
           printf("Lumiere gauche et droite eteintent !\n") ;
           wiringPiI2CWriteReg8 (Mcp, GPIO, LEDNOT) ; // On eteint tout.
           delay (100);
           EtatLed = LEDNOT ;
           EtatLedD = 0 ;
           BtnAppuiLong () ;
           goto debut ;
         }
         if (EtatLedG == 1 && EtatLedD == 1) // Si Led gauche allumer et Led droite allumer
         {
           printf("Lumiere gauche allumer et droite eteinte !\n") ;
           wiringPiI2CWriteReg8 (Mcp, GPIO, LEDG) ; // On ne laisse allumer que les leds gauche.
           delay (100) ;
           EtatLed = LEDG ;
           EtatLedD = 0 ;
           BtnAppuiLong () ;
           goto debut ;
         }
       }
   }
 delay (100); // Vitesse de la boucle
}
return 0 ;
}
