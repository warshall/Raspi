#include <stdio.h>
#include <wiringPi.h> //Il faut declarer la librairie wiring.h


#define	LED	0 //Ensuite on definit LED = 0 c est la broche 11 du raspi

int main (void)
{
  int i, allumer, eteindre, nbr, compteur; //Declaration des variables

  i=0;
  allumer = 500;
  eteindre = 500;
  compteur = 0;
  nbr= 10;

  printf ("Temps niveau haut en miliseconde ?\n");
  scanf ("%d", &allumer);
  printf ("Temps niveau bas en miliseconde ?\n");
  scanf ("%d", &eteindre);
  printf ("Nombre de fois ?\n");
  scanf ("%d", &nbr);

  if (wiringPiSetup () == -1)
    return 1 ;

  pinMode (LED, OUTPUT) ;
  nbr *=2;

  while (compteur < nbr)
{

 compteur++;

  if (i == 0)
  {
    digitalWrite (LED, 1) ;	// On
    printf("ON\n");
    delay (allumer);
    i=1;
  }
  else
  {
    digitalWrite (LED, 0) ;	// Off
    printf("OFF\n");
    delay (eteindre);
    i=0;
  }
}

  return 0 ;
}
