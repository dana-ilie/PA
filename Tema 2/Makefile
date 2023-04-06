CC = g++
CFLAGS = -Wall -Wextra -std=c++17

build:
	$(CC) $(CFLAGS) curatare.cpp -o curatare
	$(CC) $(CFLAGS) fortificatii.cpp -o fortificatii
	# $(CC) $(CFLAGS) beamdrone.cpp -o beamdrone
	$(CC) $(CFLAGS) curse.cpp -o curse

run-p1: curatare
	./curatare

run-p2: fortificatii
	./fortificatii

run-p3 : beamdrone
	./beamdrone

run-p4 : curse
	./curse

clean:
	rm -f *.o
