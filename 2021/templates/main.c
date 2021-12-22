#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <limits.h>
#include <stdint.h>
#include <math.h>

#include "aoclib.h"

#if 1
#define INPUT_FILE "./src/#DAY#/sample.txt"
#else
#define INPUT_FILE "./src/#DAY#/inputs.txt"
#endif

void part_one(char *input) {}

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
