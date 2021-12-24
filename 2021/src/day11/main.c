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
#define INPUT_FILE "./src/day11/sample.txt"
#else
#define INPUT_FILE "./src/day11/inputs.txt"
#endif

#define N 10
#define NN N *N

static bool flashed[NN];

void print_board(int board[NN]) {
  for (int i = 0; i < NN; i++) {
    if (i > 0 && i % N == 0) printf("\x1b[0m\n");
    printf("\x1b[0;%sm%d", board[i] == 0 ? "31" : "2", board[i]);
  }
  printf("\x1b[0m\n------------------------------\n");
}

int flash(int board[NN], int x, int y) {
  int i = x + y * N;

  board[i] = 0;
  flashed[i] = true;

  int flashes = 0;

  for (int dy = -1; dy <= 1; dy++) {
    for (int dx = -1; dx <= 1; dx++) {
      const int y1 = y + dy;
      const int x1 = x + dx;

      if ((y1 >= 0 && y1 < N) && (x1 >= 0 && x1 < N)) {
        i = x1 + N * y1;
        if (flashed[i]) continue;

        if (board[i] == 9)
          flashes += flash(board, x1, y1);
        else
          board[i] += 1;
      }
    }
  }

  return flashes + 1;
}

int update_board(int board[NN]) {
  memset(flashed, false, sizeof(flashed));
  int flashes = 0;

  for (int i = 0; i < NN; i++) {
    if (flashed[i]) continue;

    if (board[i] == 9)
      flashes += flash(board, i % N, i / N);
    else
      board[i] += 1;
  }

  return flashes;
}

void part_one(char *input) {
  int board[NN] = {};
  int flashes = 0;
  memset(board, 0, sizeof(board));

  for (int i = 0; *input != 0 && i < NN; input++) {
    if (*input == '\n') continue;
    board[i++] = *input - '0';
  }

  for (int i = 0; i < 100; i++) {
    flashes += update_board(board);
    // print_board(board);
  }
  printf("FLASHED %d TIMES\n", flashes);
}

void part_two(char *input) {
  int board[NN] = {};
  memset(board, 0, sizeof(board));

  for (int i = 0; *input != 0 && i < NN; input++) {
    if (*input == '\n') continue;
    board[i++] = *input - '0';
  }

  int i = 0;
  while (true) {
    i++;

    int flashes = update_board(board);
    // print_board(board);
    if (flashes == NN) break;
  }
  printf("SYNCHRONIZED AFTER %d STEPS\n", i);
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
