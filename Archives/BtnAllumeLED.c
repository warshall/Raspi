#include <stdio.h>
#include <wiringPi.h> // Il faut declarer la librairie wiring.h


#define	LED	7 // Emplacement de la LED sur la broche 7 du raspberry (Pin 7 en wiringPi Pin)
#define BTN	0 // Emplacement du bouton sur la broche 11 du raspberry (Pin 0 en wiringPi Pin)


void AllumeEteind () //Fonction qui permet d'allumer et d'eteindre la LED
{

 if (digitalRead (LED) == 0) // On teste si la LED est eteinte

  {
    digitalWrite (LED, 1) ; // LED eteinte alors on l'allume
    printf("Coucou je suis allumer\n") ; // Et on dit coucou je suis allumer
  }

 else // Sinon

  {
    digitalWrite (LED, 0) ; // On eteind la LED
    printf("Coucou je suis eteind\n") ; // Et on dit aussi coucou je suis eteind
  }
}


int main (void)
{

if (wiringPiSetup () == -1) // Si erreur d'initialisation alors stop
   return 1 ;

  pinMode (LED, OUTPUT) ; // Definit LED comme une sortie
  pinMode (BTN, INPUT) ; // Definit BTN comme entee
  digitalWrite (LED, 0) ; // Par default on eteind la LED au lancement du programe


for(;;) // Boucle infini

  {
    if (digitalRead (BTN) == 0) // Si bouton presser alors.. logique inverse a cause du montage

     {
       delay (10) ; // On attend 10ms et on refait une lecture car on peut avoir des parasites

        if (digitalRead (BTN) == 0) // On confirme que le bouton es bien presser

         {
           AllumeEteind () ; // On appelle la fonction pour allumer ou eteindre

           while (digitalRead (BTN) == 0) // Boucle pour eviter les clignotements

            {
              delay (20) ; // Attendre 20ms
            }
         }
     }

   delay (100) ; // Vitesse de la boucle 100ms

  }
 return 0 ;
}
