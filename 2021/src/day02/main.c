#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#if 0
#define INPUT_FILE "./src/day02/sample.txt"
#else
#define INPUT_FILE "./src/day02/inputs.txt"
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

  fclose(file);
  return content;
}

typedef enum { FORWARD = 7, UP = 2, DOWN = 4 } InstructionKind;

typedef struct {
  InstructionKind inst;
  int value;
} Instruction;

Instruction next_instruction(char **input) {
  int offset = 0;

  InstructionKind instruction = -1;

  for (char ch = **input;; ch = (*input)[offset++]) {
    if (ch == ' ') {
      instruction = (InstructionKind)(offset - 1);
    }
    if (ch == '\n' || ch == '\0') {
      const int value = atoi((*input) + instruction + 1);
      *input += offset;

      return (Instruction){.inst = instruction, .value = value};
    }
  }
}

void part_one() {
  char *inputs = read_file();
  char *ptr = inputs;

  int x = 0, yp = 0, yn = 0;

  int *table[] = {[FORWARD] = &x, [UP] = &yn, [DOWN] = &yp};

  do {
    Instruction inst = next_instruction(&inputs);

    *table[inst.inst] += inst.value;

  } while (*inputs != 0);

  const int y = yp - yn;

  printf("x\ty\n%d\t%d\n\nx * y = %d\n", x, y, x * y);

  free(ptr);
}

void part_two() {
  char *inputs = read_file();
  char *ptr = inputs;

  int x = 0, ap = 0, an = 0, y = 0;

  int *table[] = {[FORWARD] = &x, [UP] = &an, [DOWN] = &ap};

  do {
    Instruction inst = next_instruction(&inputs);

    *table[inst.inst] += inst.value;
    if (inst.inst == FORWARD) {
      y += (ap - an) * inst.value;
    }

  } while (*inputs != 0);

  const int aim = ap - an;
  printf("x\taim\ty\n%d\t%d\t%d\n\nx * y = %d\n", x, aim, y, x * y);

  free(ptr);
}

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
