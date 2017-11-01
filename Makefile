# -*- indent-tabs-mode:t; -*-

CC=clang
CFLAGS=-g
NUM_HASHES=20
ROCKYOU=rockyou100.txt

all: hashpass crack

hashpass: hashpass.o md5.o
	$(CC) hashpass.o md5.o -o hashpass -l ssl -l crypto

md5.o: md5.c md5.h
	$(CC) $(CFLAGS) -c md5.c -Wall

hashpass.o: hashpass.c md5.h
	$(CC) $(CFLAGS) -c hashpass.c -Wall


crack: crack.o md5.o
	$(CC) crack.o md5.o -o crack -l ssl -l crypto


crack.o: crack.c md5.h
	$(CC) $(CFLAGS) -c crack.c -Wall

hashes: hashpass
	shuf -n $(NUM_HASHES) $(ROCKYOU) > passwords.txt
	./hashpass < passwords.txt > hashes.txt

hashes.txt: hashes

clean:
	rm -f *.o hashpass crack hashes.txt passwords.txt

test: crack hashes.txt
	./crack hashes.txt $(ROCKYOU)

check: crack hashes.txt
	valgrind ./crack hashes.txt $(ROCKYOU)
