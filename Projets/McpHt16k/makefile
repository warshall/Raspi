all: btnled

btnled: main.o fonctions.o
	gcc -o btnled main.o fonctions.o -lwiringPi -lpthread
	
main.o: main.c main.h fonctions.h
	gcc -o main.o -c main.c -lwiringPi -lpthread
	
fonctions.o: fonctions.c fonctions.h
	gcc -o fonctions.o -c fonctions.c -lwiringPi

clean:
	rm -rf btnled
	rm -rf *.o
	
