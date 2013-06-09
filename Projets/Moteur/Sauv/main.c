#include<stdio.h>
#include<errno.h>
#include<wiringPi.h>
#include<wiringPiI2C.h>
#include<pthread.h>
#include"main.h"

#define IODIR   0x00 // GPIO en OUTPUT 0 ou INPUT 1.
#define GPIO	0x09 // Registre des GPIO

struct arg_jeux
{
int Mcp ;
int J ;
int *EtatLed ;
int Ht16k ;
};

void* Jeux(void* data)
{
 int *Temps = data ;
 
 for (;;)
 {
printf ("ced");
delay (20) ;
wiringPiI2CWriteReg8 (0x20, 0x09, 0x01) ;
delayMicroseconds (1500) ;
wiringPiI2CWriteReg8 (0x20, 0x09, 0x00) ;
 }

}


int main (void) // Fonction principale
{
  int Mcp, Temps ; // Declaration des variables.
  int i = 1 ;
  pthread_t Thread_Jeux;

if ((Mcp = wiringPiI2CSetup (0x20)) == -1)
 {
   fprintf (stderr, "Mcp: impossible d'initialiser l'I2C: %s\n", strerror (errno)) ; return 1 ; // Si impossible a initialiser.
 }

 Temps = (1500) ;
 pthread_create (&Thread_Jeux, NULL, Jeux, &Temps);
 wiringPiI2CWriteReg8 (Mcp, IODIR, 0x00) ; // Toutes les broches en OUTPUT
 wiringPiI2CWriteReg8 (Mcp, GPIO, 0x00) ; // Eteindre toutes les LEDs

debut:  
printf ("Combien de temps ?\n");
scanf ("%d", &Temps) ;

goto debut ;


  
//	    pthread_cancel(Thread_Jeux);	




return 0 ;
}
