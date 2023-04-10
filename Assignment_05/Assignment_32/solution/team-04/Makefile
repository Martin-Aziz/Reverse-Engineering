
crackme: crackme.o
	gcc crackme.o -o crackme

crackme.o: crackme.c
	gcc -Wno-format-security -c crackme.c -o crackme.o

clean:
	rm crackme.o
	rm crackme
