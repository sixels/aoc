#include <assert.h>
#include <limits.h>
#include <math.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "aoclib.h"

#if 1
#define INPUT_FILE "./src/day14/sample.txt"
#else
#define INPUT_FILE "./src/day14/inputs.txt"
#endif

#define ALPHABET 25

static char rules[ALPHABET][ALPHABET] = {{}};

// The lenght of the polymer can be calculated with
// 2**n * initial_len - 2**n + 1
// Where `n` is the current step
static inline size_t polymer_len(size_t initial_len, size_t n) {
  return pow(2, n) * initial_len - pow(2, n) + 1;
}

void apply_rules(char a, char b, int steps, size_t counts[ALPHABET]) {
  if (steps <= 0) return;

  char out = rules[a - 'A'][b - 'A'];

  counts[out - 'A']++;

  // printf("%c%c%c", a, out, b);

  apply_rules(out, b, steps - 1, counts);
  apply_rules(a, out, steps - 1, counts);
}

void part_one(char *input) {
  static size_t counts[ALPHABET] = {};
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
    apply_rules(template[i], template[i + 1], steps, counts);
    // printf("\n");
  }
  counts[template[template_len - 1] - 'A']++;

  size_t most_common = 0;
  size_t least_common = SIZE_MAX;
  size_t final_size = 0;

  for (size_t i = 0; i < ALPHABET; i++) {
    const size_t qty = counts[i];
    if (qty) {
      most_common = max(most_common, qty);
      least_common = min(least_common, qty);
      final_size += qty;
      printf("%c: %lu\n", (char)(i + 'A'), qty);
    }
  }

  assert(final_size == polymer_len(template_len, steps));

  // What do you get if you take the quantity of the most common element and
  // subtract the quantity of the least common element?
  printf("Most Common - Least Common: %lu\n", most_common - least_common);
}

void part_two(char *input) {
  // static size_t counts[ALPHABET] = {};

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

  // The resulting polymer isn't nearly strong enough to reinforce the
  // submarine. You'll need to run more steps of the pair insertion process; a
  // total of 40 steps should do it.

  const int steps = 40;

  size_t counts[ALPHABET][ALPHABET] = {0};
  memset(counts, 0, sizeof(counts));

  for (size_t i = 0; i < template_len - 1; i++) {
    const char a = template[i], b = template[i + 1];
    counts[a - 'A'][b - 'A']++;
  }

  size_t aux[ALPHABET][ALPHABET] = {0};
  for (size_t i = 0; i < steps; i++) {
    memset(aux, 0, sizeof(aux));
    for (int a = 0; a < ALPHABET; a++) {
      for (int b = 0; b < ALPHABET; b++) {
        char c = rules[a][b];
        if (c) {
          size_t n = counts[a][b];
          aux[a][c - 'A'] += n;
          aux[c - 'A'][b] += n;
        }
      }
    }
    memcpy(counts, aux, sizeof(aux));
  }

  size_t freq[ALPHABET];
  memset(freq, 0, sizeof(freq));
  for (int a = 0; a < ALPHABET; a++) {
    for (int b = 0; b < ALPHABET; b++) {
      freq[a] += counts[a][b];
    }
  }
  freq[template[template_len - 1] - 'A']++;

  size_t most_common = 0;
  size_t least_common = SIZE_MAX;
  size_t final_size = 0;
  for (size_t i = 0; i < ALPHABET; i++) {
    if (freq[i] > 0) {
      final_size += freq[i];
      most_common = max(most_common, freq[i]);
      least_common = min(least_common, freq[i]);
    }
  }

  assert(final_size == polymer_len(template_len, steps));

  // What do you get if you take the quantity of the most common element and
  // subtract the quantity of the least common element?
  printf("Most Common - Least Common: %lu\n", most_common - least_common);
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
