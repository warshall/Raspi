#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
void* Jeux (void* data);

struct arg_jeux
{
int Mcp ;
int J ;
int *EtatLed ;
int Ht16k ;
};

 
int main ()
{
int EtatLed = 0x26 ;
int i = 3 ;

struct arg_jeux ced = {0x00, 2, &EtatLed, 0x01} ;
printf ("%d\n", &ced) ;


pthread_t Thread_Jeux;

pthread_create (&Thread_Jeux, NULL, Jeux, &ced);

pthread_join (Thread_Jeux, NULL);
return 0;

}


void* Jeux(void* data)
{
struct arg_jeux *e = data ;
int i = e->J ;
int *p = e->EtatLed ;
printf ("%d\n",*p); 

printf ("%d\n", i) ;

return NULL;
}
