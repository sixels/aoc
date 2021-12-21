CC := gcc
CFLAGS := -Wall -Wextra -Wshadow -Ilib -g

all:
	day01 day02 day03 day04 day05 day06 day07 


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

.PHONY: day05
day05:
	$(CC) $(CFLAGS) -DPARTONE -o build/$@.1.out ./src/day05/main.c lib/aoclib.c
	$(CC) $(CFLAGS) -DPARTTWO -o build/$@.2.out ./src/day05/main.c lib/aoclib.c

.PHONY: day06
day06:
	$(CC) $(CFLAGS) -DPARTONE -o build/$@.1.out ./src/day06/main.c lib/aoclib.c
	$(CC) $(CFLAGS) -DPARTTWO -o build/$@.2.out ./src/day06/main.c lib/aoclib.c

.PHONY: day07
day07:
	$(CC) $(CFLAGS) -DPARTONE -o build/$@.1.out ./src/day07/main.c lib/aoclib.c
	$(CC) $(CFLAGS) -DPARTTWO -o build/$@.2.out ./src/day07/main.c lib/aoclib.c
