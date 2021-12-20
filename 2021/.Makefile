CC := gcc
CFLAGS := -Wall -Wextra -Wshadow -Ilib -g

all:
	day01 day02 day03 day04 day05 


.PHONY: day01
day01:
	$(CC) $(CFLAGS) -DPARTONE -o build/$@.1.out ./src/day01/main.c
	$(CC) $(CFLAGS) -DPARTTWO -o build/$@.2.out ./src/day01/main.c

.PHONY: day02
day02:
	$(CC) $(CFLAGS) -DPARTONE -o build/$@.1.out ./src/day02/main.c
	$(CC) $(CFLAGS) -DPARTTWO -o build/$@.2.out ./src/day02/main.c

.PHONY: day03
day03:
	$(CC) $(CFLAGS) -DPARTONE -o build/$@.1.out ./src/day03/main.c
	$(CC) $(CFLAGS) -DPARTTWO -o build/$@.2.out ./src/day03/main.c

.PHONY: day04
day04:
	$(CC) $(CFLAGS) -DPARTONE -o build/$@.1.out ./src/day04/main.c
	$(CC) $(CFLAGS) -DPARTTWO -o build/$@.2.out ./src/day04/main.c

.PHONY: day05
day05:
	$(CC) $(CFLAGS) -DPARTONE -o build/$@.1.out ./src/day05/main.c
	$(CC) $(CFLAGS) -DPARTTWO -o build/$@.2.out ./src/day05/main.c
