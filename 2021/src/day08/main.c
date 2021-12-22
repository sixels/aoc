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
  while (**input < 'a' || **input > 'g') {
    if (**input == '\0') return NULL;
    (*input)++;
  }

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

    // go through the 4 output digits
    for (int i = 0; i < 4; i++) {
      const char *digit = next_digit(&input);
      const int len = input - digit;

      n += (len >= 2 && len <= 4) || len == 7;
    }

  } while (*input);

  printf("Digits appears: %d times\n", n);
}

const int segment_table[] = {
    ['a'] = 1 << 0, ['b'] = 1 << 1, ['c'] = 1 << 2, ['d'] = 1 << 3,
    ['e'] = 1 << 4, ['f'] = 1 << 5, ['g'] = 1 << 6,
};

int segments_to_bits(const char *segments, int len) {
  int bits = 0;
  for (int i = 0; i < len; i++) {
    bits |= segment_table[(int)segments[i]];
  }
  return bits;
}
int count_bits(int bits) {
  int count = 0;
  while (bits) {
    if (bits & 1) count++;
    bits >>= 1;
  }

  return count;
}

int index_for_len_five(const int numbs[10], const int bits) {
  // 3 have 2 segments in common with 1, while 2 and 5 have 1 segments in common
  // with 1.
  // 5 have 3 segments in common with 4, while 2 have only 1.

  return count_bits(bits & numbs[1]) == 2   ? 3
         : count_bits(bits & numbs[4]) == 3 ? 5
                                            : 2;
}

void part_two(char *input) {
  uint64_t total = 0;

  do {
    int numbs[10] = {-1, 0, 0, 0, 0, 0, 0, 0, 127, 0};
    char *len_five[3] = {};

    // get the inputs
    while (*(input + 1) != '|') {
      char *segments = next_digit(&input);
      const int len = input - segments;

      if (len == 2) {
        numbs[1] = segments_to_bits(segments, len);
      } else if (len == 3) {
        numbs[7] = segments_to_bits(segments, len);
      } else if (len == 4) {
        numbs[4] = segments_to_bits(segments, len);
      } else if (len == 5) {
        const int i = (len_five[0] != NULL) + (len_five[1] != NULL);
        len_five[i] = segments;
      }
    };

    for (int i = 0; i < 3; i++) {
      char *segments = len_five[i];
      const int bits = segments_to_bits(segments, 5);
      numbs[index_for_len_five(numbs, bits)] = bits;
    }

    numbs[9] = numbs[5] | numbs[1];
    numbs[6] = (numbs[8] ^ numbs[3]) | numbs[5];

    uint64_t n = 0;

    // get the outputs and sum the total
    while (*input && *input != '\n') {
      const char *segments = next_digit(&input);
      const int len = input - segments;

      const int bits = segments_to_bits(segments, len);

      for (int i = 1; i < 10; i++) {
        if (numbs[i] == bits) {
          n = 10 * n + i;
          goto continue_outer;
        }
      }
      n *= 10;
    continue_outer:
    };
    total += n;
  } while (*input);

  printf("TOTAL: %lu\n", total);
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
