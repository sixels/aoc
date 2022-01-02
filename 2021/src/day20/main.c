#include <assert.h>
#include <limits.h>
#include <math.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "aoclib.h"

#define PAD 2
#define PAD2 (2 * PAD)

#if 0
#define INPUT_FILE "./src/day20/sample.txt"
#define N_COLS (5 + PAD2)
#else
#define INPUT_FILE "./src/day20/inputs.txt"
#define N_COLS (100 + PAD2)
#endif
#define INPUT_IMAGE_SIZE (N_COLS * N_COLS)

#define N_RULES 0x200  // (0b111_111_111 + 1)

void print_image(uint8_t *img, int16_t cols) {
  for (int16_t y = 0; y < cols; y++) {
    for (int16_t x = 0; x < cols; x++) {
      printf("%c", img[x + y * cols] ? '#' : '.');
    }
    printf("\n");
  }
  printf("---------------------\n");
}

void parse_inputs(char *inputs, uint8_t rules[N_RULES], uint8_t *input_image) {
  char *ruls = toktok(&inputs, "\n");
  assert(inputs++ - ruls - 1 == N_RULES);

  for (size_t i = 0; i < N_RULES; i++) {
    rules[i] = ruls[i] == '#';
  }

  char *img = toktok(&inputs, "\0");
  size_t img_len = inputs - img - 1, img_pixel = 0;
  for (size_t i = 0; i < img_len; i++) {
    if (img[i] == '\n') continue;

    int16_t x = (img_pixel % (N_COLS - PAD2)) + PAD;
    int16_t y = (img_pixel / (N_COLS - PAD2)) + PAD;
    img_pixel++;

    input_image[x + y * N_COLS] = img[i] == '#';
  }
}

static inline bool in_padl(int16_t v) { return v <= PAD; }
static inline bool in_padr(int16_t v, int16_t boundary) {
  return v >= boundary - 1 - PAD;
}

void enhance_image(uint8_t rules[N_RULES], uint8_t **img, int16_t *cols,
                   uint64_t *count) {
  assert(cols && *cols > 0);

  uint8_t *aux = malloc(*cols * *cols * sizeof(**img));
  memcpy(aux, *img, *cols * *cols * sizeof(**img));

  const int16_t out_cols = *cols + PAD2;
  const size_t out_size = out_cols * out_cols;

  uint8_t universe = rules[aux[0] ? N_RULES - 1 : 0];

  *img = realloc(*img, out_size * sizeof(**img));
  memset(*img, universe, out_size * sizeof(**img));

  for (int16_t y = 0; y < out_cols; y++) {
    for (int16_t x = 0; x < out_cols; x++) {
      uint16_t rule = 0;

      if (in_padl(y) || in_padl(x) || in_padr(y, out_cols) ||
          in_padr(x, out_cols))
        continue;

      for (int8_t dy = -1; dy <= 1; dy++) {
        for (int8_t dx = -1; dx <= 1; dx++) {
          int16_t iy = (y - PAD) + dy;
          int16_t ix = (x - PAD) + dx;

          uint8_t pixel = ((iy < 0 || ix < 0) || (iy >= *cols || ix >= *cols)
                               ? universe
                               : aux[ix + iy * *cols]);
          rule = (rule << 1) | pixel;
        }
      }
      uint8_t pixel = rules[rule];
      *count += pixel;

      (*img)[x + y * out_cols] = pixel;
    }
  }

  *cols = out_cols;
}

void part_one(char *input) {
  uint8_t rules[N_RULES];
  uint8_t *image = calloc(INPUT_IMAGE_SIZE, sizeof(uint8_t));
  parse_inputs(input, rules, image);

  int16_t cols = N_COLS;
  uint64_t count = 0;

  for (int i = 0; i < 2; i++) {
    print_image(image, cols);
    count = 0;
    enhance_image(rules, &image, &cols, &count);
  }
  print_image(image, cols);

  printf("Lit pixels: %lu\n", count);

  free(image);
}

void part_two(char *input) {
    uint8_t rules[N_RULES];
  uint8_t *image = calloc(INPUT_IMAGE_SIZE, sizeof(uint8_t));
  parse_inputs(input, rules, image);

  int16_t cols = N_COLS;
  uint64_t count = 0;

  for (int i = 0; i < 50; i++) {
    // print_image(image, cols);
    count = 0;
    enhance_image(rules, &image, &cols, &count);
  }
  print_image(image, cols);

  printf("Lit pixels: %lu\n", count);

  free(image);
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
