#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "aoclib.h"

#if 0
#define INPUT_FILE "./src/day03/sample.txt"
#define BITSLEN 5
#else
#define INPUT_FILE "./src/day03/inputs.txt"
#define BITSLEN 12
#endif

void print_bits(int *bits) {
  for (int i = 0; i < BITSLEN; i++) {
    printf("%d ", bits[i]);
  }
  printf("\n");
}

void next_bits(char **input, int *bits, int *sum) {
  int offset = 1;
  int i = 0;
  for (char ch = **input;; ch = (*input)[offset++]) {
    if (ch == '\0' || ch == '\n') {
      *input += offset;
      break;
    }

    if (bits)
      bits[i] = ch - '0';
    if (sum)
      sum[i] += ch - '0';

    i++;
  }
}

void part_one() {
  char *inputs = read_file(INPUT_FILE);
  char *ptr = inputs;

  int sum[BITSLEN] = {};
  memset(sum, 0, BITSLEN * sizeof(int));

  int lines = 0;
  do {
    next_bits(&inputs, NULL, sum);
    // print_bits(bits);
    lines++;
  } while (*inputs != 0);

  int mean = lines / 2, g = 0, e = 0;

  for (int b = 0; b < BITSLEN; b++) {
    g |= (sum[b] > mean) << (BITSLEN - b - 1);
    e |= (sum[b] < mean) << (BITSLEN - b - 1);
  }

  printf("Power consumption = %d\n", g * e);

  free(ptr);
}

typedef struct trie {
  int n;
  struct trie *next[2];
} Trie;

void part_two() {
  char *inputs = read_file(INPUT_FILE);
  char *ptr = inputs;

  int bits[BITSLEN] = {};
  int sum[BITSLEN] = {};

  memset(bits, 0, BITSLEN * sizeof(int));
  memset(sum, 0, BITSLEN * sizeof(int));

  Trie *trie = malloc(sizeof(Trie));
  Trie *aux = trie;
  do {
    next_bits(&inputs, bits, sum);
    aux = trie;
    for (int b = 0; b < BITSLEN; b++) {
      int bit = bits[b];

      if (aux->next[bit] == NULL) {

        Trie *next = malloc(sizeof(Trie));
        *next = (Trie){
            .next = {NULL, NULL},
            .n = 0,
        };

        aux->next[bit] = next;
      }

      aux->next[bit]->n += 1;
      aux = aux->next[bit];
    }
  } while (*inputs != 0);

  int oxygen = 0;
  int co2 = 0;
  Trie *oxygen_trie = trie;
  Trie *co2_trie = trie;

  for (int b = 0; b < BITSLEN; b++) {
    Trie *p1 = NULL, *p2 = NULL;

    if (oxygen_trie) {
      int z = oxygen_trie->next[0] ? oxygen_trie->next[0]->n : 0;
      int o = oxygen_trie->next[1] ? oxygen_trie->next[1]->n : 0;

      int mcb = o >= z;

      oxygen |= mcb << (BITSLEN - b - 1);
      p1 = oxygen_trie;
      oxygen_trie = oxygen_trie->next[mcb];
    }

    if (co2_trie) {

      int z = co2_trie->next[0] ? co2_trie->next[0]->n : 100000000;
      int o = co2_trie->next[1] ? co2_trie->next[1]->n : 100000000;

      int lcb = o < z;

      co2 |= lcb << (BITSLEN - b - 1);
      p2 = co2_trie;
      co2_trie = co2_trie->next[lcb];
    }

    // clean everything on the go
    if (p1 == p2) {
      free(p1);
    } else {
      free(p1);
      free(p2);
    }
  }

  printf("Oxygen = %d\nCO_2 = %d\nLife supporting rating: %d\n", oxygen, co2,
         oxygen * co2);

  free(ptr);
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
