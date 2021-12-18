#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#if 1
#define INPUT_FILE "./src/#DAY#/sample.txt"
#else
#define INPUT_FILE "./src/#DAY#/inputs.txt"
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

void part_one() {}

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
