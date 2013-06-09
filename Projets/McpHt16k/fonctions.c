#include<stdio.h>
#include<wiringPiI2C.h>
#include"fonctions.h"

void Afficher (int Matrice, int Caractere)
{
int Tab[8] ;

wiringPiI2CWrite (Matrice, 0x21) ;



if (Caractere == 1)
{
Tab[7]  =  0b00000100 ;
Tab[6]  =  0b00001100 ;
Tab[5]  =  0b00010100 ;
Tab[4]  =  0b00100100 ;
Tab[3]  =  0b00000100 ;
Tab[2]  =  0b00000100 ;
Tab[1]  =  0b00000100 ;
Tab[0]  =  0b00011111 ;

Aff (Matrice, Tab) ;
}


if (Caractere == 2)
{

Tab[7]  =  0b00111111 ;
Tab[6]  =  0b00000001 ;
Tab[5]  =  0b00000001 ;
Tab[4]  =  0b00111111 ;
Tab[3]  =  0b00100000 ;
Tab[2]  =  0b00100000 ;
Tab[1]  =  0b00100000 ;
Tab[0]  =  0b00111111 ;

Aff (Matrice, Tab) ;
}

if (Caractere == 3)
{

Tab[7]  =  0b00111111 ;
Tab[6]  =  0b00000001 ;
Tab[5]  =  0b00000001 ;
Tab[4]  =  0b00111111 ;
Tab[3]  =  0b00000001 ;
Tab[2]  =  0b00000001 ;
Tab[1]  =  0b00000001 ;
Tab[0]  =  0b00111111 ;

Aff (Matrice, Tab) ;
}

if (Caractere == 4)
{

Tab[7]  =  0b00000111 ;
Tab[6]  =  0b00001001 ;
Tab[5]  =  0b00010001 ;
Tab[4]  =  0b00100001 ;
Tab[3]  =  0b11111111 ;
Tab[2]  =  0b00000001 ;
Tab[1]  =  0b00000001 ;
Tab[0]  =  0b00000001 ;

Aff (Matrice, Tab) ;
}

if (Caractere == 5)
{

Tab[7]  =  0b00111111 ;
Tab[6]  =  0b00100000 ;
Tab[5]  =  0b00100000 ;
Tab[4]  =  0b00111111 ;
Tab[3]  =  0b00000001 ;
Tab[2]  =  0b00000001 ;
Tab[1]  =  0b00000001 ;
Tab[0]  =  0b00111111 ;

Aff (Matrice, Tab) ;
}

if (Caractere == 6)
{

Tab[7] = 0b00111111 ;
Tab[6] = 0b00000001 ;
Tab[5] = 0b00000001 ;
Tab[4] = 0b00000001 ;
Tab[3] = 0b00111111 ;
Tab[2] = 0b00100001 ;
Tab[1] = 0b00100001 ;
Tab[0] = 0b00111111 ;

Aff (Matrice, Tab) ;
}

if (Caractere == 7)
{

Tab[7] = 0b00111111 ;
Tab[6] = 0b00000001 ;
Tab[5] = 0b00000010 ;
Tab[4] = 0b00000100 ;
Tab[3] = 0b00000100 ;
Tab[2] = 0b00000100 ;
Tab[1] = 0b00000100 ;
Tab[0] = 0b00000100 ;

Aff (Matrice, Tab) ;
}

if (Caractere == 8)
{

Tab[7] = 0b00111111 ;
Tab[6] = 0b00100001 ;
Tab[5] = 0b00100001 ;
Tab[4] = 0b00111111 ;
Tab[3] = 0b00100001 ;
Tab[2] = 0b00100001 ;
Tab[1] = 0b00100001 ;
Tab[0] = 0b00111111 ;

Aff (Matrice, Tab) ;
}

if (Caractere == 9)
{

Tab[7] = 0b00111111 ;
Tab[6] = 0b00100001 ;
Tab[5] = 0b00100001 ;
Tab[4] = 0b00111111 ;
Tab[3] = 0b00000001 ;
Tab[2] = 0b00000001 ;
Tab[1] = 0b00000001 ;
Tab[0] = 0b00000001 ;

Aff (Matrice, Tab) ;
}

if (Caractere == 0)
{

Tab[7]  =  0b00111111 ;
Tab[6]  =  0b00100001 ;
Tab[5]  =  0b00100001 ;
Tab[4]  =  0b00100001 ;
Tab[3]  =  0b00100001 ;
Tab[2]  =  0b00100001 ;
Tab[1]  =  0b00100001 ;
Tab[0]  =  0b00111111 ;

Aff (Matrice, Tab) ;
}

}

void Aff (int Matrice, int Tab[8])
{
int Row[8], i = 0 ;

Row[0] = 0x00 ;
Row[1] = 0x02 ;
Row[2] = 0x04 ;
Row[3] = 0x06 ;
Row[4] = 0x08 ;
Row[5] = 0x0A ;
Row[6] = 0x0C ;
Row[7] = 0x0E ;


while (i < 8 )
  {
    wiringPiI2CWriteReg8 (Matrice, i*2, Tab[i]) ;
    i++ ;
  }

}
