CC := gcc
CFLAGS := -std=c11 -Wall -Wextra -Wshadow -Ilib -g -lm

all:
	day01 day02 day03 day04 day05 day06 day07 day08 day09 day10 day11 day12 day13 day14 


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

.PHONY: day08
day08:
	$(CC) $(CFLAGS) -DPARTONE -o build/$@.1.out ./src/day08/main.c lib/aoclib.c
	$(CC) $(CFLAGS) -DPARTTWO -o build/$@.2.out ./src/day08/main.c lib/aoclib.c

.PHONY: day09
day09:
	$(CC) $(CFLAGS) -DPARTONE -o build/$@.1.out ./src/day09/main.c lib/aoclib.c
	$(CC) $(CFLAGS) -DPARTTWO -o build/$@.2.out ./src/day09/main.c lib/aoclib.c

.PHONY: day10
day10:
	$(CC) $(CFLAGS) -DPARTONE -o build/$@.1.out ./src/day10/main.c lib/aoclib.c
	$(CC) $(CFLAGS) -DPARTTWO -o build/$@.2.out ./src/day10/main.c lib/aoclib.c

.PHONY: day11
day11:
	$(CC) $(CFLAGS) -DPARTONE -o build/$@.1.out ./src/day11/main.c lib/aoclib.c
	$(CC) $(CFLAGS) -DPARTTWO -o build/$@.2.out ./src/day11/main.c lib/aoclib.c

.PHONY: day12
day12:
	$(CC) $(CFLAGS) -DPARTONE -o build/$@.1.out ./src/day12/main.c lib/aoclib.c
	$(CC) $(CFLAGS) -DPARTTWO -o build/$@.2.out ./src/day12/main.c lib/aoclib.c

.PHONY: day13
day13:
	$(CC) $(CFLAGS) -DPARTONE -o build/$@.1.out ./src/day13/main.c lib/aoclib.c
	$(CC) $(CFLAGS) -DPARTTWO -o build/$@.2.out ./src/day13/main.c lib/aoclib.c

.PHONY: day14
day14:
	$(CC) $(CFLAGS) -DPARTONE -o build/$@.1.out ./src/day14/main.c lib/aoclib.c
	$(CC) $(CFLAGS) -DPARTTWO -o build/$@.2.out ./src/day14/main.c lib/aoclib.c
