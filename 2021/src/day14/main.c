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
#define INPUT_FILE "./src/day14/sample.txt"
#else
#define INPUT_FILE "./src/day14/inputs.txt"
#endif

#define ALPHABET 25

static size_t final_size = 0;
static char rules[ALPHABET][ALPHABET] = {{}};

// The lenght of the polymer can be calculated with
// 2**n * initial_len - 2**n + 1
// Where `n` is the current step
static inline size_t polymer_len(size_t initial_len, size_t n) {
  return (2 << (n - 1)) * initial_len - (2 << (n - 1)) + 1;
}

void apply_rules(char a, char b, int steps, int counts[ALPHABET]) {
  if (steps <= 0) return;

  char out = rules[a - 'A'][b - 'A'];

  counts[out - 'A']++;
  final_size++;

  // printf("%c%c -> %c ", a, b, out);

  apply_rules(out, b, steps - 1, counts);
  apply_rules(a, out, steps - 1, counts);
}

void part_one(char *input) {
  static int counts[ALPHABET] = {};
  memset(counts, 0, sizeof(counts));

  // The first line is the polymer template
  char *template = toktok(&input, "\n");
  size_t template_len = input++ - template - 1;

  // The following section defines the pair insertion rules. A rule like AB -> C
  // means that when elements A and B are immediately adjacent, element C should
  // be inserted between them. These insertions all happen simultaneously.
  memset(rules, 0, sizeof(rules));
  while (*input) {
    char in[2] = {input[0], input[1]};
    char *_out = toktok(&input, "\n");
    char out = _out[input - _out - 2];

    rules[in[0] - 'A'][in[1] - 'A'] = out;
  }

  // Apply 10 steps of pair insertion to the polymer template and find the most
  // and least common elements in the result.
  const int steps = 10;

  for (size_t i = 0; i < template_len - 1; i++) {
    counts[template[i] - 'A']++;
    final_size++;
    apply_rules(template[i], template[i + 1], steps, counts);
    // printf("\n");
  }
  counts[template[template_len - 1] - 'A']++;
  final_size++;

  printf("Got %lu. Expected %lu\n", final_size,
         polymer_len(template_len, steps));
  assert(final_size == polymer_len(template_len, steps));

  int most_common = INT_MIN;
  int least_common = INT_MAX;
  for (int i = 0; i < ALPHABET; i++) {
    const int qty = counts[i];
    if (qty) {
      most_common = max(most_common, qty);
      least_common = min(least_common, qty);
      printf("%c: %d\n", i + 'A', qty);
    }
  }

  // What do you get if you take the quantity of the most common element and
  // subtract the quantity of the least common element?
  printf("Most Common - Least Common: %d\n", most_common - least_common);
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
