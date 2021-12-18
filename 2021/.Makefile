CC := gcc
CFLAGS := -Wall -Wextra -Wshadow
PART := PARTONE

all:
	day03 day02 day01 


.PHONY: day03
day03:
	$(CC) $(CFLAGS) -DPARTONE -o build/$@.1.out ./src/day03/main.c
	$(CC) $(CFLAGS) -DPARTTWO -o build/$@.2.out ./src/day03/main.c

.PHONY: day02
day02:
	$(CC) $(CFLAGS) -DPARTONE -o build/$@.1.out ./src/day02/main.c
	$(CC) $(CFLAGS) -DPARTTWO -o build/$@.2.out ./src/day02/main.c

.PHONY: day01
day01:
	$(CC) $(CFLAGS) -DPARTONE -o build/$@.1.out ./src/day01/main.c
	$(CC) $(CFLAGS) -DPARTTWO -o build/$@.2.out ./src/day01/main.c
