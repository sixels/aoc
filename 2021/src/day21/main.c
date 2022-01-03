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
#define INPUT_FILE "./src/day21/sample.txt"
#else
#define INPUT_FILE "./src/day21/inputs.txt"
#endif

typedef struct {
  uint64_t pos;
  uint64_t score;
} Player;

void roll_deterministic(Player *player, uint64_t die) {
  for (short r = 0; r < 3; r++) {
    uint64_t die_face = ((die) % 100) + 1;
    assert(die_face >= 1 && die_face <= 100);

    player->pos = (((player->pos + die_face) - 1) % 10) + 1;
  }
  player->score += player->pos;
}

bool check_win(Player player) { return player.score >= 1000; }

void parse_inputs(char *inputs, Player players[2]) {
  toktok(&inputs, ":");
  char *p1_pos = inputs + 1;
  toktok(&inputs, "\n");

  toktok(&inputs, ":");
  char *p2_pos = inputs + 1;

  players[0] = (Player){
      .pos = atoi(p1_pos),
      .score = 0,
  };
  players[1] = (Player){
      .pos = atoi(p2_pos),
      .score = 0,
  };
}

void part_one(char *input) {
  Player players[2];
  parse_inputs(input, players);
  // printf("1: %lu\t2: %lu\n", players[0].pos, players[1].pos);

  uint64_t i = 1;
  short p = 0;
  while (true) {
    roll_deterministic(&players[p], i);
    i += 3;

    if (check_win(players[p])) break;
    p = (p + 1) % 2;
  }
  short looser = (p + 1) % 2;
  uint64_t rolls = i - 1;

  printf(
      "Player1 score: %lu\nPlayer2 score: %lu\nDice rolled %lu "
      "times.\n\nSolution: %lu\n",
      players[0].score, players[1].score, rolls, players[looser].score * rolls);
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
