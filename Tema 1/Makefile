CC = g++
CFLAGS = -Wall -Wextra -std=c++17

build:
	$(CC) $(CFLAGS) walsh.cpp -o walsh
	$(CC) $(CFLAGS) prinel.cpp -o prinel
	$(CC) $(CFLAGS) statistics.cpp -o statistics
	$(CC) $(CFLAGS) crypto.cpp -o crypto

run-p1: walsh
	./walsh

run-p2: statistics
	./statistics

run-p3 : prinel
	./prinel

run-p4 : crypto
	./crypto

clean:
	rm -f *.o
