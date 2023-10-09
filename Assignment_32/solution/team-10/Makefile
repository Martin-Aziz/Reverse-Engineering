all: crackme
clean:
	rm -f crackme.o crackme

crackme: crackme.c
	gcc -o $@ $^ -fno-stack-protector
