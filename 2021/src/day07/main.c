#include <assert.h>
#include <limits.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "aoclib.h"

#if 0
#define INPUT_FILE "./src/day07/sample.txt"
#define N 17
#else
#define INPUT_FILE "./src/day07/inputs.txt"
#define N 2000
#endif

#define min(l, r) (l < r) ? l : r
#define max(l, r) (l > r) ? l : r

int fuel_consumption(int *xs, int x) {
  int consumption = 0;
  for (int px = 0; px < N; px++) {
    if (xs[px] == 0) continue;

    consumption += abs(x - px) * xs[px];
  }
  return consumption;
}

void part_one(char *input) {
  int xs[N] = {};
  memset(xs, 0, N * sizeof(int));

  int len = 0;
  do {
    const int x = next_num(&input);

    len++;
    xs[x]++;
  } while (*input);

  int middle = len / 2, median_x;
  for (int i = 0; middle > 0; i++) {
    middle -= xs[i];
    median_x = i;
  }

  int min_consumption = fuel_consumption(xs, median_x);

  printf("Min consumption: %d\n", min_consumption);
}

void part_two(char *input) {}

int main(void) {
  char *input = read_file(INPUT_FILE);

#ifdef PARTONE
  printf("Running part one...\n");
  part_one(input);
#else
  printf("Running part two...\n");
  part_two(input);
#endif

  free(input);
  return 0;
}
