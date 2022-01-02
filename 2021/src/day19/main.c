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
#define INPUT_FILE "./src/day19/sample.txt"
#define N_SCANNERS 5
#else
#define INPUT_FILE "./src/day19/inputs.txt"
#define N_SCANNERS 30
#endif

void print_scanners();

typedef union {
  struct {
    int64_t x, y, z;
  };
  int64_t v[3];
} Vec3;

Vec3 vec3(int64_t x, int64_t y, int64_t z) {
  return (Vec3){.x = x, .y = y, .z = z};
}

Vec3 vec3_translate(Vec3 *a, Vec3 b) {
  a->x += b.x;
  a->y += b.y;
  a->z += b.z;
  return *a;
}
Vec3 vec3_diff(Vec3 a, Vec3 b) { return vec3(a.x - b.x, a.y - b.y, a.z - b.z); }

// (xa-xb)^2 + (ya-yb)^2 + (za-zb)^2
int64_t vec3_sq_distance(Vec3 a, Vec3 b) {
  Vec3 diff = vec3_diff(a, b);
  return diff.x * diff.x + diff.y * diff.y + diff.z * diff.z;
}

typedef struct {
  uint8_t i;
  Vec3 beacons[30];
  size_t nbeacons;

  bool aligned;
} Scanner;

typedef enum {
  XY,
  YZ,
  ZX,
} Axis2d;

static Scanner scanners[30];

static Vec3 adjusted_beacons[30 * N_SCANNERS];
static size_t ab_len = 0;

static int64_t rotation[24][3][3] = {
    {{1, 0, 0}, {0, 1, 0}, {0, 0, 1}},    {{1, 0, 0}, {0, 0, -1}, {0, 1, 0}},
    {{1, 0, 0}, {0, -1, 0}, {0, 0, -1}},  {{1, 0, 0}, {0, 0, 1}, {0, -1, 0}},
    {{0, -1, 0}, {1, 0, 0}, {0, 0, 1}},   {{0, 0, 1}, {1, 0, 0}, {0, 1, 0}},
    {{0, 1, 0}, {1, 0, 0}, {0, 0, -1}},   {{0, 0, -1}, {1, 0, 0}, {0, -1, 0}},
    {{-1, 0, 0}, {0, -1, 0}, {0, 0, 1}},  {{-1, 0, 0}, {0, 0, -1}, {0, -1, 0}},
    {{-1, 0, 0}, {0, 1, 0}, {0, 0, -1}},  {{-1, 0, 0}, {0, 0, 1}, {0, 1, 0}},
    {{0, 1, 0}, {-1, 0, 0}, {0, 0, 1}},   {{0, 0, 1}, {-1, 0, 0}, {0, -1, 0}},
    {{0, -1, 0}, {-1, 0, 0}, {0, 0, -1}}, {{0, 0, -1}, {-1, 0, 0}, {0, 1, 0}},
    {{0, 0, -1}, {0, 1, 0}, {1, 0, 0}},   {{0, 1, 0}, {0, 0, 1}, {1, 0, 0}},
    {{0, 0, 1}, {0, -1, 0}, {1, 0, 0}},   {{0, -1, 0}, {0, 0, -1}, {1, 0, 0}},
    {{0, 0, -1}, {0, -1, 0}, {-1, 0, 0}}, {{0, -1, 0}, {0, 0, 1}, {-1, 0, 0}},
    {{0, 0, 1}, {0, 1, 0}, {-1, 0, 0}},   {{0, 1, 0}, {0, 0, -1}, {-1, 0, 0}},
};

struct rot_result {
  Vec3 r[24]
} rotated(Vec3 v) {
  struct rot_result re;

  for (int i = 0; i < 24; i++) {
    int64_t x = rotation[i][0][0] * v.x + rotation[i][0][1] * v.y +
                rotation[i][0][2] * v.z;
    int64_t y = rotation[i][1][0] * v.x + rotation[i][1][1] * v.y +
                rotation[i][1][2] * v.z;
    int64_t z = rotation[i][2][0] * v.x + rotation[i][2][1] * v.y +
                rotation[i][2][2] * v.z;

    re.r[i] = vec3(x, y, z);
  }

  return re;
}

void save_beacons(size_t n, Vec3 bs[n]) {
  for (size_t b = 0; b < n; b++) {
    bool is_dup = false;
    for (size_t ab = 0; !is_dup && ab < ab_len; ab++)
      is_dup = memcmp(&adjusted_beacons[ab], &bs[b], sizeof(Vec3)) == 0;

    if (!is_dup) adjusted_beacons[ab_len++] = bs[b];
  }
}

void translate_all_vec(size_t n, Vec3 dst[n], Vec3 src) {
  for (size_t i = 0; i < n; i++) {
    vec3_translate(&dst[i], src);
  }
}

void rot_nbeacons(size_t n, Vec3 beacons[n], int r) {
  for (size_t b = 0; b < n; b++) {
    beacons[b] = rotated(beacons[b]).r[r];
  }
}

struct distmap {
  int64_t vs[50000];
  uint64_t freqs[50000];
  size_t len;
};

struct distmap xdist_map;
struct distmap ydist_map;
struct distmap zdist_map;

void clear_dms() {
  memset(&xdist_map, 0, sizeof(struct distmap));
  memset(&ydist_map, 0, sizeof(struct distmap));
  memset(&zdist_map, 0, sizeof(struct distmap));
}

bool push_dm(struct distmap *dm, int64_t dist) {
  bool found = false;
  size_t i = 0;

  for (i = 0; !found && i < dm->len; i++) {
    found = dm->vs[i] == dist;
  }

  if (!found) {
    dm->vs[i] = dist;
    dm->freqs[i] = 0;
    dm->len++;
  }
  dm->freqs[i - found]++;

  return found;
}

bool dm12(struct distmap *dm, int64_t *v) {
  bool has12 = false;

  struct {
    size_t i;
    uint64_t freq;
  } max = {.i = 0, .freq = 12};

  for (size_t i = 0; i < dm->len; i++) {
    if (dm->freqs[i] >= max.freq) {
      has12 = true;
      max.freq = dm->freqs[i];
      max.i = i;
    }
  }

  *v = dm->vs[max.i];
  return has12;
}

void align_scanner(Scanner *s) {
  if (s->aligned) return;

  for (int r = 0; r < 24; r++) {
    Vec3 beacons[30];
    memcpy(beacons, s->beacons, sizeof(s->beacons));
    rot_nbeacons(s->nbeacons, beacons, r);

    clear_dms();
    for (size_t b = 0; b < s->nbeacons; b++) {
      Vec3 beacon = beacons[b];

      for (size_t ab = 0; ab < ab_len; ab++) {
        Vec3 abeacon = adjusted_beacons[ab];
        Vec3 diff = vec3_diff(abeacon, beacon);
        push_dm(&xdist_map, diff.x);
        push_dm(&ydist_map, diff.y);
        push_dm(&zdist_map, diff.z);
      }
    }

    bool xoff = false, yoff = false, zoff = false;
    int64_t xv = 0, yv = 0, zv = 0;
    xoff = dm12(&xdist_map, &xv);
    yoff = dm12(&ydist_map, &yv);
    zoff = dm12(&zdist_map, &zv);

    if (xoff && yoff && zoff) {
      Vec3 origin = vec3(xv, yv, zv);
      // printf("Origin: %ld,%ld,%ld\n", xv, yv, zv);

      memcpy(s->beacons, beacons, sizeof(s->beacons));

      translate_all_vec(s->nbeacons, beacons, origin);
      save_beacons(s->nbeacons, beacons);

      s->aligned = true;
      return;
    }
  }
}

void part_one(char *input) {
  size_t beacons = 0;
  size_t scanners_len = 0;

  // parse inputs
  do {
    input++;
    // if (*input == '\n')
    toktok(&input, "\n");
    Scanner *scanner = &scanners[scanners_len];
    scanner->i = scanners_len++;

    while (*input && *input != '\n') {
      char *coords = toktok(&input, "\n");
      size_t coords_len = input - coords - 1;

      for (size_t i = 0; i < 3; i++) {
        char *coord = tokntok(&coords, coords_len + 1, ",\n");
        scanner->beacons[scanner->nbeacons].v[i] = (int64_t)atoi(coord);
      }
      beacons++;
      scanner->nbeacons++;
      scanner->aligned = false;
    }
  } while (*input && *(input - 1));

  scanners[0].aligned = true;
  save_beacons(scanners[0].nbeacons, scanners[0].beacons);

  bool aligned[N_SCANNERS];
  memset(aligned, 0, sizeof(aligned));

  for (size_t i = 1;; i = (i + 1) % N_SCANNERS) {
    Scanner *s = &scanners[i];

    align_scanner(s);
    aligned[s->i] = s->aligned;
    printf("%d -> %d\n", s->i, s->aligned);

    bool all_aligned = true;
    for (size_t j = 0; j < N_SCANNERS; j++) {
      all_aligned &= aligned[j];
    }
    if (all_aligned) break;
  }

  for (size_t i = 0; i < N_SCANNERS; i++) {
    assert(scanners[i].aligned);
  }

  printf("N beacons: %lu\n", ab_len);
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

void print_scanners() {
  for (size_t i = 0; i < N_SCANNERS; i++) {
    printf("Scanner %ld: ", i);
    Scanner scanner = scanners[i];
    for (size_t j = 0; j < scanner.nbeacons; j++) {
      printf("(%ld,%ld,%ld) ", scanner.beacons[j].x, scanner.beacons[j].y,
             scanner.beacons[j].z);
    }
    printf("\n");
  }
}