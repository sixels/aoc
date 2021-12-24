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

static int32_t *lookup;
static uint32_t rows = 0;

enum { RIGHT = 0, LEFT = 1, UP = 2, DOWN = 3 } Directions;

const int8_t directions[4][2] = {
    [RIGHT] = {1, 0},
    [LEFT] = {-1, 0},
    [UP] = {0, -1},
    [DOWN] = {0, 1},
};

bool is_lowpoint(int32_t *hm, uint32_t i, int32_t v) {
  for (int d = 0; d < 4; d++) {
    int32_t x = (i % COLS) + directions[d][0];
    int32_t y = (i / COLS) + directions[d][1];

    if ((x >= 0 && x < COLS) && (y >= 0 && y < (int32_t)rows)) {
      if (v > hm[x + y * COLS]) return false;
    }
  };
  return true;
}

void part_one(char *input) {
  size_t hm_capacity = 100, hm_len = 0;
  int32_t *hm = malloc(hm_capacity * sizeof(int32_t));

  // get the inputs
  do {
    while (*input < '0' || *input > '9') {
      if (!*input) break;
      input++;
    }

    if (hm_len >= hm_capacity) {
      hm_capacity *= 2;
      hm = realloc(hm, hm_capacity * sizeof(int32_t));
    }

    hm[hm_len++] = *(input++) - '0';
  } while (*input);

  rows = hm_len / COLS;

  uint32_t risk = 0;
  for (uint32_t i = 0; i < hm_len; i++) {
    const uint32_t v = hm[i];
    risk += is_lowpoint(hm, i, v) * (v + 1);
  }

  printf("RISK LEVEL: %d\n", risk);

  free(hm);
}

uint32_t search_neighbour(int32_t *hm, uint32_t i, int32_t v) {
  uint32_t size = 0;

  if (lookup[i] >= 0) return size;
  lookup[i] = hm[i];

  for (int d = 0; d < 4; d++) {
    int32_t x = (i % COLS) + directions[d][0];
    int32_t y = (i / COLS) + directions[d][1];
    if ((x >= 0 && x < COLS) && (y >= 0 && y < (int32_t)rows)) {
      int32_t height = hm[x + y * COLS];
      if (height >= v && height < 9) {
        size += search_neighbour(hm, x + y * COLS, v);
      }
    }
  }

  return size + 1;
}

void insert_largest(uint32_t (*lbasins)[3], uint32_t size) {
  uint32_t b = 0;
  for (int i = 0; i < 3; i++) {
    if ((*lbasins)[i] < size) {
      b = b >> 2 < size - (*lbasins)[i] ? ((size - (*lbasins)[i]) << 2) | i : b;
    }
  }
  if (b) {
    (*lbasins)[b & 3] = size;
  }
}

void part_two(const char *input) {
  size_t hm_capacity = 100, hm_len = 0;
  int32_t *hm = malloc(hm_capacity * sizeof(int32_t));

  // get the inputs
  do {
    while (*input < '0' || *input > '9') {
      if (!*input) break;
      input++;
    }

    if (hm_len >= hm_capacity) {
      hm_capacity *= 2;
      hm = realloc(hm, hm_capacity * sizeof(int32_t));
    }

    hm[hm_len++] = *(input++) - '0';
  } while (*input);

  rows = hm_len / COLS;

  lookup = malloc(hm_len * sizeof(int32_t));
  memset(lookup, -1, hm_len * sizeof(int32_t));

  uint32_t lbasins[3] = {0, 0, 0};
  for (uint32_t i = 0; i < hm_len; i++) {
    const int32_t v = hm[i];

    if (is_lowpoint(hm, i, v)) {
      const int32_t size = search_neighbour(hm, i, v);
      insert_largest(&lbasins, size);
    }
  }

  // cool visualizer
  // for (size_t i = 0; i < hm_len; i++) {
  //   if (i % COLS == 0) printf("\x1b[0m\n");
  //   printf("\x1b[4%dm%d", lookup[i] > 0 ? lookup[i] : 0,
  //          lookup[i] == -1 ? hm[i] : lookup[i]);
  // }
  // printf("\x1b[0m\n");

  printf("LARGEST BASINS SIZE: %d %d %d\n", lbasins[0], lbasins[1], lbasins[2]);
  printf("RESULT: %d\n", lbasins[0] * lbasins[1] * lbasins[2]);

  free(hm);
  free(lookup);
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
