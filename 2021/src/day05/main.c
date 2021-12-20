#include <assert.h>
#include <limits.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "aoclib.h"

#if 0
#define INPUT_FILE "./src/day05/sample.txt"
#define N 10
#else
#define INPUT_FILE "./src/day05/inputs.txt"
#define N 1000
#endif

#define min(l, r) (l <= r ? l : r)
#define max(l, r) (l >= r ? l : r)

void part_one(char *input) {
  int overlaps = 0;
  int board[N][N] = {{}};

  // parse points
  do {
    const int x1 = next_num(&input);
    const int y1 = next_num(&input);

    const int x2 = next_num(&input);
    const int y2 = next_num(&input);


    if (x2 != x1 && y2 != y1) continue;

    const int minx = min(x1, x2), maxx = max(x1, x2);
    const int miny = min(y1, y2), maxy = max(y1, y2);


    for (int y = miny; y <= maxy; y++) {
      for (int x = minx; x <= maxx; x++) {
        overlaps += ++board[y][x] == 2;
      }
    }

    // debug
    // for (int y = 0; y < N; y++) {
    //   for (int x = 0; x < N; x++) {
    //     int point = board[y][x];
    //     printf("%c", point ? point + '0' : '.');
    //   }
    //   printf("\n");
    // }
    // printf("=======================\n");

  } while (*input != '\0');

  printf("Overlaps: %d\n", overlaps);
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
