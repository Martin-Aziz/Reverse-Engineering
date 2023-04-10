# fno-stack-protector			-> disable stack canaries
# no-pie 				-> disable ASLR
# Wno-implicit-function-declaration	-> disable 'implicit function declaration' warning

CC=gcc
CC-OPT=-fno-stack-protector -no-pie -Wno-implicit-function-declaration

.PHONY: all clean

all: crackme

crackme: crackme.c
	$(CC) $(CC-OPT) -o crackme crackme.c

clean:
	rm crackme
