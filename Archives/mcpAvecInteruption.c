#include<stdio.h>
#include<errno.h>
#include<wiringPi.h>
#include<wiringPiI2C.h>

#define IODIR	0x00 // GPIO en OUTPUT 0 ou INPUT 1.
#define GPINTEN	0x02 // Activer les interuptions si 1, le MCP retient l'entrer qui a changer de valeur.
		     // Si 0 il ne ce passe rien.
#define INTCON	0x04 // Si 1 changement d'etat prit en compte par rapport a une valeur par default.
		     // Si 0 changement d'etat prit en compte par rapport a l'ancien etat.
#define DEFVAL	0x03 // Valeur de l'entrer par default. Utilse si votre entrer est a 1 par default.
#define INTF	0x07 // Retourne la valeur en hexa de l'entrer qui a ete activer.
#define GPIO	0x09 // En lisant ce registre on RAZ le registre 0x07 sinon il retient la valeur et ne prend pas en
		     // compte les nouveaux etat si il y a d'autres entrer.
#define BTNG	0x40 // Valeur hexa du bouton gauche.
#define BTND	0x80 // Valeur hexa du bouton droit.
#define LEDG	0x07 // Allumer les leds a gauche
#define LEDD	0x38 // Allumer les leds a droite
#define LEDALL	0x3F // Allumer toutes les leds
#define LEDNOT	0x00 // Eteindre toutes les leds.

int RazINTF (void) // Fonction qui permet de RAZ INTF
{

 wiringPiI2CReadReg8 ((wiringPiI2CSetup (0x20)), GPIO) ; // Il suffit de lire le registre GPIO (0x09)

}


int main (void) // Fonction principale
{

 int Mcp, EtatLedG, EtatLedD, EtatBTNG ; // Declaration des variables.

if ((Mcp = wiringPiI2CSetup (0x20)) == -1)
{
 fprintf (stderr, "Mcp: impossible d'initialiser l'I2C: %s\n", strerror (errno)) ; return 1 ; // Si impossible a initialiser.
}


 EtatLedG = 0 ; // Initialisation des variables
 EtatLedD = 0 ;

 wiringPiI2CWriteReg8 (Mcp, IODIR, 0xC0) ; // Toutes les broches en OUTPUT sauf broches 6 et 7 en input.
 wiringPiI2CWriteReg8 (Mcp, GPINTEN, 0xC0) ; // Definit les interuptions sur broche 6 et 7.
 wiringPiI2CWriteReg8 (Mcp, INTCON, 0xC0) ; // Compare la valeur par rapport a une valeur par default.
 wiringPiI2CWriteReg8 (Mcp, DEFVAL, 0xC0) ; // Les entrer du montage sont a un niveau haut par default. (+3.3v)

 wiringPiI2CWriteReg8 (Mcp, GPIO, LEDNOT) ; // Eteindre toutes les LEDs
 RazINTF () ; // On reinitialise INTF.

for (;;)
{

debut: //Etiquette goto je ne sai pas faire autrement..

   if (wiringPiI2CReadReg8 (Mcp, INTF) == BTNG) // Si bouton gauche presser alors...
   {
     delay (10); // On attend 10ms puis on fait une relecture pour etre sur que ce n'est pas un parasite
       if (wiringPiI2CReadReg8 (Mcp, INTF) == BTNG) // Si bouton gauche presser..
       {

         if (EtatLedG == 0 && EtatLedD == 0) // Si led gauche et droite sont eteintent
         {
          printf("Lumiere gauche allumer !\n") ;
          wiringPiI2CWriteReg8 (Mcp, GPIO, LEDG) ; // Allumage des LED a gauche
          delay (100); // Attendre 100ms
          RazINTF () ; // On Raz INTF
          EtatLedG = 1 ; // On specifi que les Led a gauche sont allumer.
          goto debut ; // On revient au debut de la boucle sinon execution de la condition suivante.
         }
       if (EtatLedG == 1 && EtatLedD == 0) // Si led gauche allumer et led droite eteintent
         {
          printf("Lumiere gauche et droite eteintent !\n") ;
          wiringPiI2CWriteReg8 (Mcp, GPIO, LEDNOT) ; // On eteind tout.
          delay (100) ;
          RazINTF () ;
          EtatLedG = 0 ;
          goto debut ;
         }
       if (EtatLedG == 0 && EtatLedD == 1) // Si Led gauche eteintent et led droite allumer
         {
          printf("Lumiere gauche et droite allumer !\n") ;
          wiringPiI2CWriteReg8 (Mcp, GPIO, LEDALL) ; // On allume tout.
          delay (100);
          RazINTF () ;
          EtatLedG = 1 ;
          goto debut ;
         }
       if (EtatLedG == 1 && EtatLedD == 1) // Si Led gauche allumer et Led droite allumer
         {
          printf("Lumiere gauche eteint et droite allumer !\n") ;
          wiringPiI2CWriteReg8 (Mcp, GPIO, LEDD) ; // On allume que les leds droite.
          delay (100) ;
          RazINTF () ;
          EtatLedG = 0 ;
          goto debut ;
         }
       }
   }


if (wiringPiI2CReadReg8 (Mcp, INTF) == BTND) // Si bouton droit presser alors...
   {
     delay (10); // On attend 10ms puis on fait une relecture pour etre sur que ce n'est pas un parasite
       if (wiringPiI2CReadReg8 (Mcp, INTF) == BTND) // Si bouton droit presser..
       {

         if (EtatLedG == 0 && EtatLedD == 0) // Si les leds gauche et droite sont eteintent
         {
          printf("Lumiere droite allumer !\n") ;
          wiringPiI2CWriteReg8 (Mcp, GPIO, LEDD) ; // On allume que les leds droite
          delay (100);
          RazINTF () ;
          EtatLedD = 1 ;
          goto debut ;
         }
       if (EtatLedG == 1 && EtatLedD == 0) // Si Led gauche allumer et Led droite eteintent
         {
          printf("Lumiere gauche et droite allumer !\n") ;
          wiringPiI2CWriteReg8 (Mcp, GPIO, LEDALL) ; // On allume toutes les leds
          delay (100) ;
          RazINTF () ;
          EtatLedD = 1 ;
          goto debut ;
         }
       if (EtatLedG == 0 && EtatLedD == 1) // Si Led gauche eteintent et droite allumer
         {
          printf("Lumiere gauche et droite eteintent !\n") ;
          wiringPiI2CWriteReg8 (Mcp, GPIO, LEDNOT) ; // On eteint tout.
          delay (100);
          RazINTF () ;
          EtatLedD = 0 ;
          goto debut ;
         }
       if (EtatLedG == 1 && EtatLedD == 1) // Si Led gauche allumer et Led droite allumer
         {
          printf("Lumiere gauche allumer et droite eteinte !\n") ;
          wiringPiI2CWriteReg8 (Mcp, GPIO, LEDG) ; // On ne laisse allumer que les leds gauche.
          delay (100) ;
          RazINTF () ;
          EtatLedD = 0 ;
          goto debut ;
         }
       }
   }
 delay (500); // Vitesse de la boucle
}
return 0 ;
}
