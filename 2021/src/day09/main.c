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
#define INPUT_FILE "./src/day09/sample.txt"
#define COLS 10
#else
#define INPUT_FILE "./src/day09/inputs.txt"
#define COLS 100
#endif

void part_one(char *input) {
  size_t hm_capacity = 100, hm_len = 0;
  uint32_t *hm = malloc(hm_capacity * sizeof(uint32_t));

  // get the inputs
  do {
    while (*input < '0' || *input > '9') {
      if (!*input) break;
      input++;
    }

    if (hm_len >= hm_capacity) {
      hm_capacity *= 2;
      hm = realloc(hm, hm_capacity * sizeof(uint32_t));
    }

    hm[hm_len++] = *(input++) - '0';
  } while (*input);

  const uint32_t rows = hm_len / COLS;

  uint32_t risk = 0;
  for (uint32_t i = 0; i < hm_len; i++) {
    const uint32_t x = i % COLS, y = i / COLS;

    uint32_t v = hm[i];
    uint32_t r = (x + 1 != COLS) ? hm[i + 1] : UINT32_MAX,
             l = (x != 0) ? hm[i - 1] : UINT32_MAX,
             u = (y != 0) ? hm[x + (y - 1) * COLS] : UINT32_MAX,
             d = (y + 1 != rows) ? hm[x + (y + 1) * COLS] : UINT32_MAX;

    risk += (v < l && v < r && v < u && v < d) * (v + 1);
  }

  printf("RISK LEVEL: %d\n", risk);

  free(hm);
}

void part_two(const char *input) {}

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
