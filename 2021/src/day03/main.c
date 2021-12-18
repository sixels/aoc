#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#if 0
#define INPUT_FILE "./src/day03/sample.txt"
#define BITSLEN 5
#else
#define INPUT_FILE "./src/day03/inputs.txt"
#define BITSLEN 12
#endif

char *read_file() {
  FILE *file = fopen(INPUT_FILE, "r");

  if (file == NULL) {
    fprintf(stderr, "Could not find file %s\n", INPUT_FILE);
    exit(1);
  }

  fseek(file, 0, SEEK_END);
  size_t file_size = ftell(file);
  rewind(file);

  char *content = malloc(file_size + 1);
  fread(content, sizeof(char), file_size, file);

  return content;
}

void print_bits(int *bits) {
  for (int i = 0; i < BITSLEN; i++) {
    printf("%d ", bits[i]);
  }
  printf("\n");
}

void next_bits(char **input, int *bits) {
  int offset = 1;
  int i = 0;
  for (char ch = **input;; ch = (*input)[offset++]) {
    if (ch == '\0' || ch == '\n') {
      *input += offset;
      break;
    }

    bits[i++] += ch - '0';
  }
}

void part_one() {
  char *inputs = read_file();
  char *ptr = inputs;

  int bits[BITSLEN] = {};
  memset(bits, 0, BITSLEN * sizeof(int));

  int lines = 0;
  do {
    next_bits(&inputs, bits);
    // print_bits(bits);
    lines++;
  } while (*inputs != 0);

  int mean = lines / 2, g = 0, e = 0;

  for (int b = 0; b < BITSLEN; b++) {
    g |= (bits[b] > mean) << (BITSLEN - b - 1);
    e |= (bits[b] < mean) << (BITSLEN - b - 1);
  }

  printf("Power consumption = %d\n", g * e);

  free(ptr);
}

void part_two() {}

int main(void) {
#ifdef PARTONE
  printf("Running part one...\n");
  part_one();
#else
  printf("Running part two...\n");
  part_two();
#endif
  return 0;
}
