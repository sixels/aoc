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
#define INPUT_FILE "./src/day13/sample.txt"
#define N 15
#else
#define INPUT_FILE "./src/day13/inputs.txt"
#define N 1500
#endif

void print_paper(int *paper, int xl, int yl) {
  for (int y = 0; y < yl; y++) {
    for (int x = 0; x < xl; x++) {
      printf("%c", paper[y * N + x] ? '#' : '.');
    }
    printf("\n");
  }
  printf("================\n");
}

void part_one(char *input) {
  // get the coords

  int *paper = calloc(N * N, sizeof(int));
  int paper_x = N, paper_y = N, maxx = 0, maxy = 0;

  int dots = 0;

  while (*input && *input != '\n') {
    const int x = atoi(toktok(&input, ","));
    const int y = atoi(toktok(&input, "\n"));

    maxx = max(x, maxx);
    maxy = max(y, maxy);

    paper[y * paper_x + x] = 1;
    dots++;
    // printf("%d,%d\n", x, y);
  }

  paper_x = maxx + 1;
  paper_y = maxy + 1;
  print_paper(paper, paper_x, paper_y);

  // fold
  while (*input) {
    char *_axis = toktok(&input, "=");
    bool x_axis = _axis[(int)(input - _axis) - 2] == 'x';

    int offset = atoi(toktok(&input, "\n"));

    int table[2][2] = {
        // y     x
        {offset, 0},  // axis != x
        {0, offset}   // axis == x
    };

    for (int y = table[x_axis][0]; y < paper_y; y++) {
      for (int x = table[x_axis][1]; x < paper_x; x++) {
        if (paper[y * N + x] == 1) {
          const int yoff = x_axis ? 0 : offset, xoff = x_axis ? offset : 0;

          const int y1 = yoff ? 2 * yoff - y : y, x1 = xoff ? 2 * xoff - x : x;

          if (x1 >= 0 && y1 >= 0) {
            dots -= paper[y1 * N + x1] != 0;
            paper[y1 * N + x1] = 1;
          }
        }
      }
    }

    paper_y -= table[x_axis][0];
    paper_x -= table[x_axis][1];
    print_paper(paper, paper_x, paper_y);
    break;
  }
  free(paper);

  printf("AMOUNT OF DOTS: %d\n", dots);
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
