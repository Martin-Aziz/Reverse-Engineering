.PHONY: all clean
all: crackme

clean:
	rm -f crackme.o

main: crackme.o
	gcc -o -s crackme crackme.o

crackme.o: crackme.c
	gcc -Wall -c crackme.c
