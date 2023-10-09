.PHONY: all
all: crackme

%.o: %.c
	gcc -Wall -g -c $<

.PHONY: test
test: crackme
	./crackme > /tmp/a && ../crackme > /tmp/b && diff /tmp/a /tmp/b

.PHONY: clean
clean:
	rm crackme
