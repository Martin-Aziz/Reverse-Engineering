ENCRYPTION_KEY = "index_shuffle"

all: crackme

run: crackme
	./crackme

crackme: crackme.c
	cc -Wall -O0 $^ -o $@

crackme.c: main.c payload.bin encrypt zeroes.bin
	@echo "merge payload.bin"
	$(shell cat zeroes.bin >> payload.bin)
	$(eval BYTES := $(shell cat payload.bin | ./encrypt $(ENCRYPTION_KEY) | od - -t u1 | grep -Po "\b\d{1,3}\b" | paste -sd "," -))
	@sed -e "s/112, 114, 111, 103, 114, 97, 109/$(BYTES)/g" main.c > $@

encrypt: encrypt.cpp
	g++ -Wall $^ -o $@

payload.bin: payload.o
	objcopy -O binary -j .text $^ $@

payload.o: payload.c
	cc -Wall -c $^ -o $@

clean:
	rm payload.o payload.bin encrypt crackme.c crackme
