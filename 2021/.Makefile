CC := gcc
CFLAGS := -Wall -Wextra -Wshadow -Ilib -g

all:
	day01 day02 day03 day04


.PHONY: day01
day01:
	$(CC) $(CFLAGS) -DPARTONE -o build/$@.1.out ./src/day01/main.c lib/aoclib.c
	$(CC) $(CFLAGS) -DPARTTWO -o build/$@.2.out ./src/day01/main.c lib/aoclib.c

.PHONY: day02
day02:
	$(CC) $(CFLAGS) -DPARTONE -o build/$@.1.out ./src/day02/main.c lib/aoclib.c
	$(CC) $(CFLAGS) -DPARTTWO -o build/$@.2.out ./src/day02/main.c lib/aoclib.c

.PHONY: day03
day03:
	$(CC) $(CFLAGS) -DPARTONE -o build/$@.1.out ./src/day03/main.c lib/aoclib.c
	$(CC) $(CFLAGS) -DPARTTWO -o build/$@.2.out ./src/day03/main.c lib/aoclib.c

.PHONY: day04
day04:
	$(CC) $(CFLAGS) -DPARTONE -o build/$@.1.out ./src/day04/main.c lib/aoclib.c
	$(CC) $(CFLAGS) -DPARTTWO -o build/$@.2.out ./src/day04/main.c lib/aoclib.c
