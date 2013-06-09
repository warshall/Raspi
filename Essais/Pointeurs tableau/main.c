#include<stdio.h>

void main ()
{
int Tab[4] = {1,2,3,4} ;
int *P1 ;

P1 = &Tab[0] ;

printf ("allo %d\n", (*P1+1)) ;
}