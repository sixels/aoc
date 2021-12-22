#include <assert.h>
#include <limits.h>
#include <math.h>
#include <stdbool.h>
#include <stdint.h>
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

#define min(l, r) (l < r ? l : r)
#define max(l, r) (l > r ? l : r)

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

int64_t complex_fuel_consumption(int64_t *xs, int64_t x) {
  if (x < 0 || x > N) return INT64_MAX;

  int64_t consumption = 0;

  for (int64_t px = 0; px < N; px++) {
    if (xs[px] == 0) continue;

    // I have a feeling that `abs()` does not work properly on all int64
    int64_t dx = (int64_t)x - (int64_t)px;
    dx = max(dx, -dx);

    const int64_t middle = dx / 2;
    const int64_t burned_fuel = (dx + 1) * middle + (dx % 2) * (middle + 1);

    consumption += burned_fuel * xs[px];
  }
  printf("---- %lu: %lu fuel\n", x, consumption);
  return consumption;
}

void part_two(char *input) {
  int64_t xs[N] = {};
  memset(xs, 0, N * sizeof(int64_t));

  int64_t len = 0, sum = 0;
  do {
    const int64_t x = next_num(&input);

    sum += x;

    len++;
    xs[x]++;
  } while (*input);

  const int64_t mean = sum / len;
  int64_t min_consumption = INT64_MAX;

  for (int i = mean - 2; i <= mean + 2; i++) {
    const int64_t consumed = complex_fuel_consumption(xs, i);
    min_consumption = min(min_consumption, consumed);
  }

  printf("Min consumption: %ld\n", min_consumption);
}

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
