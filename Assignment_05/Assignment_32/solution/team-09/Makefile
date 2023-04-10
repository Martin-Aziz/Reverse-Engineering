.PHONY: all
all: crackme

crackme: crackme.c
	gcc -Wall -o $@ $^
	strip --strip-all crackme

.PHONY: test
test: crackme
	./crackme > /tmp/a && ./crackme > /tmp/b && diff /tmp/a /tmp/b

.PHONY: clean
clean:
	rm crackme
