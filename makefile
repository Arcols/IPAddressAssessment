all: main

main: main.o fonctionIP.o
	gcc main.o fonctionIP.o -o main

# Compilation de main.c en main.o
main.o: main.c fonctionIP.h
	gcc -c main.c -o main.o

# Compilation de fonctionIP.c en fonctionIP.o
fonctionIP.o: fonctionIP.c fonctionIP.h
	gcc -c fonctionIP.c -o fonctionIP.o

# nettoyage des fichiers objets et l'exécutable
clean:
	rm -f *.o main
