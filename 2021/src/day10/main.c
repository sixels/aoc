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
    [OPAR] = 1, [OBRK] = 2,  [OBRC] = 3,    [OARR] = 4,
    [CPAR] = 3, [CBRK] = 57, [CBRC] = 1197, [CARR] = 25137,
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
            printf("LINE %02d: Expected %c, but found %c instead\n", line_nr,
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

int score_sort(const void *l, const void *r) {
  const uint64_t a = *(const uint64_t*) l;
  const uint64_t b = *(const uint64_t*) r;
  return (a > b) - (a < b);
}

void part_two(char *input) {
  uint64_t scores[150] = {}, scores_len = 0;

  int line_nr = 0;
  while (*input != 0) {
    line_nr++;
    bool corrupted = false;

    Token stack[STACK_SIZE] = {};
    memset(stack, 0, sizeof(stack));
    int stack_len = 0;

    for (char c = *(input++); c != '\n' && c != '\0'; c = *(input++)) {
      if (corrupted == true) continue;

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
          corrupted = pairs[stack[i]] != c;

          break;

        default:
          break;
      }
    }

    // we want only incomplete lines
    if (corrupted == true || stack_len == 0) continue;

    uint64_t score = 0;
    for (int i = stack_len - 1; i >= 0; i--) {
      score = 5 * score + (uint64_t)points[stack[i]];
    }

    printf("LINE %02d: SCORE: %ld\n", line_nr, score);
    scores[scores_len++] = score;
  }

  qsort(&scores[0], scores_len, sizeof(uint64_t), score_sort);
  printf("MIDDLE SCORE: %lu\n", scores[scores_len / 2]);
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
