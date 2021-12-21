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
