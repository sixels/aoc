CC := gcc
CFLAGS := -Wall -Wextra -Wshadow
PART := PARTONE

all:
	day02


.PHONY: day02
day02:
	$(CC) $(CFLAGS) -DPARTONE -o build/$@.1.out ./src/day02/main.c
	$(CC) $(CFLAGS) -DPARTTWO -o build/$@.2.out ./src/day02/main.c
