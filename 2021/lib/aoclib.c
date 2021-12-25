#include "aoclib.h"

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

char *toktok(char **str, char *del) {
  if (!str || !*str) return NULL;

  char *token = *str;
  int dels[128] = {0};

  while (del && *(del)) dels[(int)*(del++)] = 1;

  while (**str) {
    char c = *((*str)++);
    if (dels[(int)c]) return token;
  }

  return token;
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