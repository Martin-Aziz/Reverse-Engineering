.PHONY: all
all: crackme

crackme: crackme.c
	gcc -g -fno-stack-protector -fno-pie -no-pie crackme.c -o crackme -lm

.PHONY: clean
clean:
	rm crackme
