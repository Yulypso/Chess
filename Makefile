all : PROJET EXECUTION CLEAN MRPROPER

PROJET : fonctions.o main.o sdl.o
	g++ -o PROJET fonctions.o main.o sdl.o -lSDL -lSDLmain

fonctions.o : fonctions.cpp headers.h 
	g++ -Wall -o fonctions.o -c fonctions.cpp -lSDLmain -lSDL
	
sdl.o : sdl.cpp headers.h
	g++ -Wall -o sdl.o -c sdl.cpp -lSDL -lSDLmain

main.o : main.cpp headers.h
	g++ -Wall -o main.o -c main.cpp -lSDL -lSDLmain

EXECUTION : 
	./PROJET

CLEAN : 
	rm -f *.o core
	
MRPROPER :
	rm -f PROJET
