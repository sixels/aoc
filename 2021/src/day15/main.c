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

static int (*visited)[2] = NULL;
static size_t visi = 0, visb = 0, vis_capacity = 0;

void visit(int x, int y) {
  int i = (visi + visb) % vis_capacity;
  visited[i][0] = x;
  visited[i][1] = y;
  visi++;
}

void leave(int *x, int *y) {
  *x = visited[visb][0];
  *y = visited[visb][1];

  visb = (visb + 1) % vis_capacity;
  visi--;
}

int directions[4][2] = {
    // x y
    {1, 0},   // right
    {-1, 0},  // left
    {0, -1},  // up
    {0, 1},   // down
};

int64_t mapped_position(const int64_t cavern[N][N], int x, int y) {
  int64_t value = cavern[y % N][x % N] + (x / N) + (y / N);
  return ((value - 1) % 9) + 1;
}

int64_t dijkstra(const int64_t cavern[N][N], uint8_t multiplier,
                 int64_t risk_map[N * multiplier][N * multiplier]) {
  const int size = N * multiplier;
  for (int y = 0; y < size; y++) {
    for (int x = 0; x < size; x++) {
      risk_map[y][x] = INT64_MAX;
    }
  }
  risk_map[0][0] = 0;

  vis_capacity = N * N * 5;
  visited = malloc(vis_capacity * sizeof(*visited));

  visit(0, 0);
  while (visi > 0) {
    int x = 0, y = 0;
    leave(&x, &y);

    for (int d = 0; d < 4; d++) {
      const int dx = x + directions[d][0], dy = y + directions[d][1];

      if ((dx >= 0 && dx < size) && (dy >= 0 && dy < size)) {
        const int64_t next_risk = mapped_position(cavern, dx, dy);

        if ((risk_map[y][x] + next_risk) < risk_map[dy][dx]) {
          risk_map[dy][dx] = risk_map[y][x] + next_risk;
          visit(dx, dy);
        }
      }
    }
  }
  free(visited);

  return risk_map[N * multiplier - 1][N * multiplier - 1];
}

void part_one(char *input) {
  int64_t cavern[N][N] = {};
  memset(cavern, 0, sizeof(cavern));

  for (int y = 0; y < N; y++) {
    for (int x = 0; x < N; x++) {
      cavern[y][x] = input[y * (N + 1) + x] - '0';
    }
  }

  int64_t risk_map[N][N] = {};
  int64_t risk = dijkstra(cavern, 1, risk_map);

  // for (int y = 0; y < N; y++) {
  //   for (int x = 0; x < N; x++) {
  //     printf("%02ld ", risk_map[y][x]);
  //   }
  //   printf("\n");
  // }

  printf("RISK LEVEL: %ld\n", risk);
}

void part_two(char *input) {
  int64_t cavern[N][N] = {};
  memset(cavern, 0, sizeof(cavern));

  for (int y = 0; y < N; y++) {
    for (int x = 0; x < N; x++) {
      cavern[y][x] = input[y * (N + 1) + x] - '0';
    }
  }

  int64_t risk_map[N * 5][N * 5] = {};
  int64_t risk = dijkstra(cavern, 5, risk_map);
  // for (int y = 0; y < N * 3; y++) {
  //   for (int x = 0; x < N * 3; x++) {
  //     printf("%ld ", risk_map[y][x]);
  //   }
  //   printf("\n");
  // }

  printf("RISK LEVEL: %ld\n", risk);
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
