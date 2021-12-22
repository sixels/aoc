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
#define INPUT_FILE "./src/day08/sample.txt"
#else
#define INPUT_FILE "./src/day08/inputs.txt"
#endif

void skip_inputs(char **input) {
  do {
    (*input)++;
  } while (**input && **input != '|');
}

char *next_digit(char **input) {
  char *digit = *input;

  while (**input >= 'a' && **input <= 'g') {
    (*input)++;
  }

  return digit;
}

void part_one(char *input) {
  int n = 0;

  // skip the left part of the input, we only need the output values
  do {
    skip_inputs(&input);

    // skip the "| "
    input += 2;

    // go through the 4 output digits
    for (int i = 0; i < 4; i++) {
      const char *digit = next_digit(&input);
      const int len = input - digit;
      input++;

      n += (len >= 2 && len <= 4) || len == 7;
    }

  } while (*input);

  printf("Digits appears: %d times\n", n);
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
