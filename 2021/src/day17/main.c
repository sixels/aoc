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
#define INPUT_FILE "./src/day17/sample.txt"
#else
#define INPUT_FILE "./src/day17/inputs.txt"
#endif

typedef struct {
  union {
    struct {
      int x, y;
    };
    int v[2];
  };
} Vec2;

Vec2 vec2(int x, int y) { return (Vec2){.x = x, .y = y}; }

char *parse_range(char *input, int *a, int *b) {
  *a = atoi(toktok(&input, "."));
  input++;
  *b = atoi(toktok(&input, " \n"));
  return input;
}

bool intersect_area(Vec2 p, Vec2 area[2]) {
  return (p.x >= area[0].x && p.x <= area[1].x) &&
         (p.y >= area[1].y && p.y <= area[0].y);
}

bool simulate_prop(int vx, int vy, Vec2 area[2], int *max_height) {
  Vec2 pos = vec2(0, 0);

  do {
    pos.x = pos.x + vx;
    pos.y += vy;
    vx -= pos.x < 0 ? -1 : 1;
    vy -= 1;

    if (pos.y > *max_height) {
      *max_height = pos.y;
    }

    if (intersect_area(pos, area)) return true;
  } while (pos.x <= area[1].x && pos.y >= area[1].y);
  return false;
}

void part_one(char *input) {
  toktok(&input, "x");
  input++;

  int x0, x1, y0, y1;
  input = parse_range(input, &x0, &x1) + 2;
  parse_range(input, &y0, &y1);
  printf("x=%d..%d   y=%d..%d\n", x0, x1, y0, y1);

  Vec2 area[2] = {
      vec2(min(x0, x1), max(y0, y1)),  // upper-left
      vec2(max(x0, x1), min(y0, y1)),  // bottom-right
  };

  int max_height = INT_MIN;

  for (int vx = -500; vx < 500; vx++) {
    for (int vy = -500; vy < 500; vy++) {
      int height = INT_MIN;
      if (simulate_prop(vx, vy, area, &height)) {
        printf("(%d,%d) = %d\n", vx, vy, height);
        if (height > max_height) {
          max_height = height;
        }
      }
    }
  }
  printf("%d\n", max_height);
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
