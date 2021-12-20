#include <stdio.h>
#include <stdlib.h>

char *read_file(char *file_path) {
  FILE *file = fopen(file_path, "r");

  if (file == NULL) {
    fprintf(stderr, "Could not find file %s\n", file_path);
    exit(1);
  }

  fseek(file, 0, SEEK_END);
  size_t file_size = ftell(file);
  rewind(file);

  char *content = malloc(file_size + 1);
  fread(content, sizeof(char), file_size, file);

  fclose(file);
  return content;
}

int next_num(char **input) {
  while (**input < '0' || **input > '9') {
    if (**input == '\0') return 0;
    (*input)++;
  }

  char *num_str = *input;
  while (**input >= '0' && **input <= '9') (*input)++;

  return atoi(num_str);
}