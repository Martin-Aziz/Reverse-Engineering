all: crackme

crackme: crackme.c
	gcc crackme.c -lm -o crackme -fno-stack-protector -no-pie

.PHONY: clean
clean:
	rm crackme
