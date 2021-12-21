#include <assert.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "aoclib.h"

#if 0
#define INPUT_FILE "./src/day06/sample.txt"
#else
#define INPUT_FILE "./src/day06/inputs.txt"
#endif

#define N 9

void dump_days(uint64_t days[N]) {
  for (int i = 0; i < N - 1; i++) {
    printf("%lu,", days[i]);
  }
  printf("%lu\n===========\n", days[N - 1]);
}

void part_one(char *input) {
  const int n_days = 80;

  int days[N] = {};
  int total_fishs = 0;
  memset(days, 0, N * sizeof(int));

  // get the initial state
  do {
    int fish = next_num(&input);
    days[fish]++;
    total_fishs++;
  } while (*input != 0);

  // simulate
  for (int i = 0; i < n_days; i++) {
    const int last_day = days[0];
    for (int d = 0; d < N - 1; d++) {
      days[d] = days[d + 1];
    }
    days[6] += last_day;
    days[8] = last_day;
    total_fishs += last_day;
  }

  printf("Total fishs after %d days: %d\n", n_days, total_fishs);
}

void part_two(char *input) {
  uint64_t total_fishs = 0;
  const int n_days = 256;

  uint64_t days[N] = {};
  memset(days, 0, N * sizeof(uint64_t));

  // get the initial state
  do {
    int fish = next_num(&input);
    days[fish]++;
    total_fishs++;
  } while (*input != 0);

  // dump_days(days);

  // simulate
  for (int i = 0; i < n_days; i++) {
    const uint64_t last_day = days[0];
    for (int d = 0; d < N - 1; d++) {
      days[d] = days[d + 1];
    }
    days[6] += last_day;
    days[8] = last_day;
    total_fishs += last_day;
    // dump_days(days);
    // printf("day %d: %ld\n", i+1, total_fishs);
  }

  printf("Total fishs after %d days: %lu\n", n_days, total_fishs);
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
