#include<stdio.h>
#include"Presentations.h"
#include"main.h"


int main (void) // Fonction principale
{
int Choix ;
Pres PresChoix = {0,0,0,0} ;
Presentation (&PresChoix, 0) ;

debut:

scanf ("%d", &Choix) ;


Presentation (&PresChoix, Choix) ;

if (Choix == 5) {return 0 ; }

goto debut ;
/*	    pthread_cancel(Thread_Jeux);	
		pthread_create (&Thread_Jeux, NULL, Jeux, &TypeDeJeu);
        printf("coucou\n") ;
*/
return 0 ;
}
