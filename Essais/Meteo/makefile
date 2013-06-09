all: meteo

meteo: main.o Presentations.o
	gcc -o meteo main.o Presentations.o
	
main.o: main.c main.h Presentations.h
	gcc -o main.o -c main.c
	
Presentations.o: Presentations.c Presentations.h
	gcc -Wall -o Presentations.o -c Presentations.c

clean:
	rm -rf meteo
	rm -rf *.o
	
