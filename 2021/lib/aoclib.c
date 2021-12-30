#include "aoclib.h"

#include <stddef.h>
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

char *toktok(char **__restrict__ str, char *__restrict__ del) {
  if (!str || !*str) return NULL;

  char *token = *str;
  char dels[128] = {0};

  while (del && *del) dels[(int)*(del++)] = 1;
  dels[0] = 1;

  while (1)
    if (dels[(int)*((*str)++)]) break;

  return token;
}

char *tokntok(char ** str, char * del, size_t n) {
  if (!str || !*str) return NULL;

  char *token = *str;
  char dels[128] = {0};

  while (del && *del) dels[(int)*(del++)] = 1;
  dels[0] = 1;

  while (n) {
    if (dels[(int)*((*str)++)]) break;
    n--;
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