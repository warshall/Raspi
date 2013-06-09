#include<stdio.h>
#include"Presentations.h"
#include"main.h"

void Presentation (Pres *Type, int Choix)
{

	switch (Choix) 
	{
		case 1:
		if (Type->Temperature == 0) {Type->Temperature = 1 ; break ; }
		if (Type->Temperature == 1) {Type->Temperature = 0 ; break ; }
		break ;

		case 2:
		if (Type->Humidite == 0) {Type->Humidite = 1 ; break ; }
		if (Type->Humidite == 1) {Type->Humidite = 0 ; break ; }
		break ;

		case 3:
		if (Type->Vent == 0) {Type->Vent = 1 ; break ; }
		if (Type->Vent == 1) {Type->Vent = 0 ; break ; }
		break ;

		case 4:
		if (Type->Tout == 0) 
		{
		Type->Temperature = 1 ;
		Type->Humidite = 1 ;
		Type->Vent = 1 ;
		Type->Tout = 1 ; 
		break ;}

		if (Type->Tout == 1) 
		{
		Type->Temperature = 0 ;
		Type->Humidite = 0 ;
		Type->Vent = 0 ;
		Type->Tout = 0 ;
		
		break ; 
		}
		break ;

}

		if (Type->Temperature == 1 && Type->Humidite == 1 && Type->Vent == 1) {Type->Tout = 1 ;}
		if (Type->Temperature == 0 && Type->Humidite == 1 && Type->Vent == 1) {Type->Tout = 0 ;}
		if (Type->Temperature == 1 && Type->Humidite == 0 && Type->Vent == 1) {Type->Tout = 0 ;}
		if (Type->Temperature == 1 && Type->Humidite == 1 && Type->Vent == 0) {Type->Tout = 0 ;}
		
printf("\n\nStation Meteo:\n\n\n") ;

if (Type->Temperature == 1 ) {printf("1 - Desactiver le senseur temperature 			**Actif**\n") ; }
else
printf("1 - Activer le senseur temperature\n") ;

if (Type->Humidite == 1) {printf("2 - Desactiver le senseur humidite 			**Actif**\n") ; }
else
printf("2 - Activer le senseur humidite\n") ;

if (Type->Vent == 1) {printf("3 - Desactiver le senseur vitesse du vent 		**Actif**\n") ; }
else
printf("3 - Activer le senseur vitesse du vent\n") ;

if (Type->Tout == 1) {printf("4 - Tout desactiver\n") ; }
else
printf("4 - Tout activer\n") ;
printf("5 - Quitter\n\n") ;
printf(": ") ;


}
