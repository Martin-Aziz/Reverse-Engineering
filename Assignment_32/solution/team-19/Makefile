CC=gcc
CC-OPT=-no-pie -O0

.PHONY: all clean

all: crackme solution

crackme: crackme.c
	$(CC) $(CC-OPT) -o crackme crackme.c

solution: solution.c
	$(CC) $(CC-OPT) -o solution solution.c

clean:
	rm crackme solution

