#include <stdio.h>
#include <wiringPi.h> //Il faut declarer la librairie wiring.h


#define	LED	0 //Ensuite on definit LED = 0 c est la broche 11 du raspi

int main (void)
{

//int pin;

if (wiringPiSetup () == -1)
    return 1 ;

//    printf ("Quelle broche utilisez vous ? (Le PIN de wiringPi)\n");
//    scanf ("%d", pin);

  pinMode (LED, INPUT) ;

for(;;)

  {
    if (digitalRead (LED) == 0)
     {
       printf ("Appuyer\n");
     }
    else
     {
       printf ("Relacher\n");
     }
 delay(1000);
  }
  return 0 ;
}
