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
#define INPUT_FILE "./src/day15/sample.txt"
#define N 10
#else
#define INPUT_FILE "./src/day15/inputs.txt"
#define N 100
#endif

int visited[N * N][2] = {{0, 0}};
size_t visited_i = 0;

void visit(int x, int y) {
  visited[visited_i][0] = x;
  visited[visited_i][1] = y;
  visited_i++;
}

void leave(int *x, int *y) {
  visited_i--;
  *x = visited[visited_i][0];
  *y = visited[visited_i][1];
}

int directions[4][2] = {
    // x y
    {1, 0},   // right
    {-1, 0},  // left
    {0, -1},  // up
    {0, 1},   // down
};

void part_one(char *input) {
  int64_t cavern[N][N] = {};
  memset(cavern, 0, sizeof(cavern));
  memset(visited, 0, sizeof(visited));

  for (int y = 0; y < N; y++) {
    for (int x = 0; x < N; x++) {
      cavern[y][x] = input[y * (N + 1) + x] - '0';
    }
  }

  int64_t risk = 0;

  int64_t risk_map[N][N] = {0};
  for (int y = 0; y < N; y++) {
    for (int x = 0; x < N; x++) {
      risk_map[y][x] = INT64_MAX;
    }
  }
  risk_map[0][0] = 0;

  visit(0, 0);
  while (visited_i > 0) {
    int x = 0, y = 0;
    leave(&x, &y);

    for (int d = 0; d < 4; d++) {
      const int dx = x + directions[d][0], dy = y + directions[d][1];

      if ((dx >= 0 && dx < N) && (dy >= 0 && dy < N)) {
        if (risk_map[y][x] + cavern[dy][dx] < risk_map[dy][dx]) {
          risk_map[dy][dx] = risk_map[y][x] + cavern[dy][dx];
          visit(dx, dy);
        }
      }
    }
  }

  risk = risk_map[N - 1][N - 1];

  // for (int y = 0; y < N; y++) {
  //   for (int x = 0; x < N; x++) {
  //     printf("%02ld ", risk_map[y][x]);
  //   }
  //   printf("\n");
  // }

  printf("RISK LEVEL: %ld\n", risk);
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
