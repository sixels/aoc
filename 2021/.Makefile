CC := gcc
CFLAGS := -Wall -Wextra -Wshadow
PART := PARTONE

all:
	day02 day01 day03


.PHONY: day02
day02:
	$(CC) $(CFLAGS) -DPARTONE -o build/$@.1.out ./src/day05/main.c
	$(CC) $(CFLAGS) -DPARTTWO -o build/$@.2.out ./src/day05/main.c

.PHONY: day01
day01:
	$(CC) $(CFLAGS) -DPARTONE -o build/$@.1.out ./src/day05/main.c
	$(CC) $(CFLAGS) -DPARTTWO -o build/$@.2.out ./src/day05/main.c

.PHONY: day03
day03:
	$(CC) $(CFLAGS) -DPARTONE -o build/$@.1.out ./src/day05/main.c
	$(CC) $(CFLAGS) -DPARTTWO -o build/$@.2.out ./src/day05/main.c
