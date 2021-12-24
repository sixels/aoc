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
#define INPUT_FILE "./src/day10/sample.txt"
#define STACK_SIZE 30
#else
#define INPUT_FILE "./src/day10/inputs.txt"
#define STACK_SIZE 150
#endif

typedef enum {
  // braces
  OBRC = '{',
  CBRC = '}',
  // brackets
  OBRK = '[',
  CBRK = ']',
  // parentheses
  OPAR = '(',
  CPAR = ')',
  // "arrows"
  OARR = '<',
  CARR = '>',
} Token;

char pairs[128] = {
    [OBRC] = CBRC, [OBRK] = CBRK, [OPAR] = CPAR, [OARR] = CARR,
    [CBRC] = OBRC, [CBRK] = OBRK, [CPAR] = OPAR, [CARR] = OARR,
};

int points[128] = {
    [CPAR] = 3,
    [CBRK] = 57,
    [CBRC] = 1197,
    [CARR] = 25137,
};

void part_one(char *input) {
  int line_nr = 0, score = 0;
  while (*input != 0) {
    line_nr++;
    bool skip = false;

    Token stack[STACK_SIZE] = {};
    memset(stack, 0, sizeof(stack));
    int stack_len = 0;

    for (char c = *(input++); c != '\n' && c != '\0'; c = *(input++)) {
      if (skip == true) continue;

      switch (c) {
        case OBRC:
        case OBRK:
        case OPAR:
        case OARR:
          stack[stack_len++] = (Token)c;
          break;

        case CBRC:
        case CBRK:
        case CPAR:
        case CARR:
          int i = --stack_len;

          if (pairs[stack[i]] != c) {
            printf("LINE %d: Expected %c, but found %c instead\n", line_nr,
                   pairs[stack[i]], c);
            score += points[(int)c];
            skip = true;
          }

          break;

        default:
          break;
      }
    }
  }

  printf("TOTAL SCORE: %d\n", score);
}

void part_two(char *input) {}

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
