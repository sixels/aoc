CC := gcc
CFLAGS := -Wall -Wextra -Wshadow
PART := PARTONE

all:
	day01


.PHONY: day01
day01:
	$(CC) $(CFLAGS) -DPARTONE -o build/$@.1.out ./src/day01/main.c
	$(CC) $(CFLAGS) -DPARTTWO -o build/$@.2.out ./src/day01/main.c
