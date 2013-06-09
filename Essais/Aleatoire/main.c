#include<stdio.h>
#include<time.h>
#include<stdlib.h>
#include<wiringPi.h>
#include<wiringPiI2C.h>

int main()
{
srand (time(NULL));
int d = rand() % 17 ;
int i = 0 ;
int Matrice = wiringPiI2CSetup (0x70) ;


for (;;)
{

i = rand() % 15 ;

d = rand() % 256 ;
wiringPiI2CWriteReg8 (Matrice, i, d) ;

delay (5) ;

}


}

