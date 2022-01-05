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
#define INPUT_FILE "./src/day22/sample.txt"
#else
#define INPUT_FILE "./src/day22/inputs.txt"
#endif

typedef int64_t Range[2];

typedef struct {
  int64_t state;
  Range x;
  Range y;
  Range z;
} Cuboid;

typedef struct {
  Cuboid cs[45000];
  size_t l;
} Cuboids;

Cuboid parse_line(char *line) {
  char *on_off = toktok(&line, " ");
  bool state = on_off[1] == 'n';

  // x
  toktok(&line, "=");
  int64_t xb = atoi(line);
  toktok(&line, ".");
  int64_t xe = atoi(line + 1);

  // y
  toktok(&line, "=");
  int64_t yb = atoi(line);
  toktok(&line, ".");
  int64_t ye = atoi(line + 1);

  // z
  toktok(&line, "=");
  int64_t zb = atoi(line);
  toktok(&line, ".");
  int64_t ze = atoi(line + 1);

  // clang-format off
  return (Cuboid) {
    .state = state ? 1 : -1,
    .x = {min(xb, xe), max(xb, xe)},
    .y = {min(yb, ye), max(yb, ye)},
    .z = {min(zb, ze), max(zb, ze)},
  };
  // clang-format on
}

static inline bool cuboid_is_valid(Cuboid c) {
  return c.x[0] <= c.x[1] && c.y[0] <= c.y[1] && c.z[0] <= c.z[1];
}
/// check if b intersects a, saving the intersection on `inte`
bool cuboid_intersects(Cuboid a, Cuboid b, Cuboid *inte) {
  // clang-format off
  *inte = (Cuboid) {
    .state = -b.state,
    .x = {max(a.x[0], b.x[0]), min(a.x[1], b.x[1])},
    .y = {max(a.y[0], b.y[0]), min(a.y[1], b.y[1])},
    .z = {max(a.z[0], b.z[0]), min(a.z[1], b.z[1])},
  };
  // clang-format on

  return cuboid_is_valid(*inte);
}

bool cuboid_is_limited(Cuboid c) {
  if (c.x[0] > 50 || c.y[0] > 50 || c.z[0] > 50) return false;
  if (c.x[1] < -50 || c.y[1] < -50 || c.z[1] < -50) return false;

  assert(cuboid_is_valid(c));
  return true;
}

void print_cuboid(Cuboid c) {
  printf("%s x=%ld..%ld,y=%ld..%ld,z=%ld..%ld\n", c.state == 1 ? "on" : "off",
         c.x[0], c.x[1], c.y[0], c.y[1], c.z[0], c.z[1]);
}

void part_one(char *input) {
  Cuboids cuboids;
  memset(&cuboids, 0, sizeof(Cuboids));

  do {
    char *line = toktok(&input, "\n");

    Cuboid c = parse_line(line);
    if (!cuboid_is_limited(c)) continue;
    print_cuboid(c);

    cuboids.cs[cuboids.l++] = c;
  } while (*input && input[-1]);

  Cuboids cores;
  memset(&cores, 0, sizeof(Cuboids));

  for (size_t i = 0; i < cuboids.l; i++) {
    Cuboids intersections;
    memset(&intersections, 0, sizeof(Cuboids));
    // check if the cuboid intercepts other cores
    for (size_t j = 0; j < cores.l; j++) {
      Cuboid intersection;
      if (cuboid_intersects(cuboids.cs[i], cores.cs[j], &intersection))
        intersections.cs[intersections.l++] = intersection;
    }
    if (cuboids.cs[i].state == 1) {
      cores.cs[cores.l++] = cuboids.cs[i];
    }
    for (size_t inter = 0; inter < intersections.l; inter++) {
      cores.cs[cores.l++] = intersections.cs[inter];
    }
  }

  int64_t result = 0;
  for (size_t i = 0; i < cores.l; i++) {
    Cuboid c = cores.cs[i];
    result += c.state * (c.x[1] - c.x[0] + 1) * (c.y[1] - c.y[0] + 1) *
              (c.z[1] - c.z[0] + 1);
  }

  printf("Solution: %ld\n", result);
}

void part_two(char *input) {
    Cuboids cuboids;
  memset(&cuboids, 0, sizeof(Cuboids));

  do {
    char *line = toktok(&input, "\n");

    Cuboid c = parse_line(line);

    cuboids.cs[cuboids.l++] = c;
  } while (*input && input[-1]);

  Cuboids cores;
  memset(&cores, 0, sizeof(Cuboids));

  for (size_t i = 0; i < cuboids.l; i++) {
    Cuboids intersections;
    memset(&intersections, 0, sizeof(Cuboids));
    // check if the cuboid intercepts other cores
    for (size_t j = 0; j < cores.l; j++) {
      Cuboid intersection;
      if (cuboid_intersects(cuboids.cs[i], cores.cs[j], &intersection))
        intersections.cs[intersections.l++] = intersection;
    }
    if (cuboids.cs[i].state == 1) {
      cores.cs[cores.l++] = cuboids.cs[i];
    }
    for (size_t inter = 0; inter < intersections.l; inter++) {
      cores.cs[cores.l++] = intersections.cs[inter];
    }
  }

  int64_t result = 0;
  for (size_t i = 0; i < cores.l; i++) {
    Cuboid c = cores.cs[i];
    // print_cuboid(c);
    result += c.state * (c.x[1] - c.x[0] + 1) * (c.y[1] - c.y[0] + 1) *
              (c.z[1] - c.z[0] + 1);
  }

  printf("Solution: %ld\n", result);
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
