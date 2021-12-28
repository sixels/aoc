#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "aoclib.h"

#if 0
#define INPUT_FILE "./src/day01/sample.txt"
#else
#define INPUT_FILE "./src/day01/inputs.txt"
#endif

int part_one() {
  char *input = read_file(INPUT_FILE);
  char *ptr = input;

  int offset = 0, last_depth = 0, increased = -1;
  for (char ch = input[0];; ch = input[offset]) {
    if (ch == '\n' || ch == '\0') {

      const int depth = atoi(input);
      if (depth > last_depth) {
        increased++;
      }
      last_depth = depth;

      input += offset;
      offset = 0;

      if (ch == '\0')
        break;
    }
    offset++;
  }
  printf("depth increased %d times\n", increased);

  free(ptr);
  return increased;
}

int part_two() {
  char *input = read_file(INPUT_FILE);
  char *ptr = input;

  int increased = -1;

  int last_depth = 0;
  int windows[] = {0, 0, 0, 0};

  // i = 0
  windows[0] = next_num(&input);

  // i = 1
  windows[1] = next_num(&input);
  windows[0] += windows[1];

  while (*input != 0) {
    const int depth = next_num(&input);
    if (depth == 0)
      break;

    windows[2] = depth;
    windows[1] += depth;
    windows[0] += depth;

    if (windows[0] > last_depth)
      increased++;
    last_depth = windows[0];
    windows[0] = windows[1];
    windows[1] = windows[2];
  };

  printf("depth increased %d times\n", increased);

  free(ptr);
  return increased;
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
