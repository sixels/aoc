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

static int WSCORE = 1000;

typedef struct {
  uint64_t pos;
  uint64_t score;
} Player;

static inline void update_position(Player *player, uint64_t n) {
  player->pos = (((player->pos + n) - 1) % 10) + 1;
}

void roll_deterministic(Player *player, uint64_t die) {
  for (short r = 0; r < 3; r++) {
    uint64_t die_face = ((die) % 100) + 1;
    assert(die_face >= 1 && die_face <= 100);

    update_position(player, die_face);
  }
  player->score += player->pos;
}

static inline bool check_win(Player player) { return player.score >= WSCORE; }

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

// {
//   [1] = {
//     [1] = {[1] = 1+1+1=3, [2] = 1+1+2=4, [3] = 1+1+3=5},
//     [2] = {[1] = 1+2+1=4, [2] = 1+2+2=5, [3] = 1+2+3=6},
//     [3] = {[1] = 1+3+1=5, [2] = 1+3+2=6, [3] = 1+3+3=7}
//   },
//   [2] = {
//     [1] = {[1] = 2+1+1=4, [2] = 2+1+2=5, [3] = 2+1+3=6},
//     [2] = {[1] = 2+2+1=5, [2] = 2+2+2=6, [3] = 2+2+3=7},
//     [3] = {[1] = 2+3+1=6, [2] = 2+3+2=7, [3] = 2+3+3=8}
//   },
//   [3] = {
//     [1] = {[1] = 3+1+1=5, [2] = 3+1+2=6, [3] = 3+1+3=7},
//     [2] = {[1] = 3+2+1=6, [2] = 3+2+2=7, [3] = 3+2+3=8},
//     [3] = {[1] = 3+3+1=7, [2] = 3+3+2=8, [3] = 3+3+3=9}
//   },
// }
// total = 27
//
// a better approach
//        |
//        v
// 3={1,1,1};
// 4={1,1,2}={1,2,1}={2,1,1};
// 5={1,1,3}={1,2,2}={1,3,1}={2,1,2}={2,2,1}={3,1,1};
// 6={1,2,3}={1,3,2}={2,1,3}={2,2,2}={2,3,1}={3,1,2}={3,2,1};
// 7={1,3,3}={2,2,3}={2,3,2}={3,1,3}={3,2,2}={3,3,1};
// 8={2,3,3}={3,2,3}={3,3,2};
// 9={3,3,3};
// total = 7
#define N_POSSIBILITIES 7
static uint64_t possibilities[N_POSSIBILITIES][2] = {
    {3, 1}, {4, 3}, {5, 6}, {6, 7}, {7, 6}, {8, 3}, {9, 1},
};
Player roll_quantum(Player player, int p) {
  uint64_t pos = possibilities[p][0];

  update_position(&player, pos);
  player.score += player.pos;

  return player;
}

uint64_t quantum_game(Player players[2], int turn) {
  Player player[N_POSSIBILITIES][2];
  uint64_t sum = 0;

  for (int p = 0; p < N_POSSIBILITIES; p++) {
    player[p][turn] = roll_quantum(players[turn], p);
    player[p][turn ^ 1] = players[turn ^ 1];
    if (check_win(player[p][turn])) {
      if (turn == 0) sum += possibilities[p][1];
    } else {
      sum += quantum_game(player[p], turn ^ 1) * possibilities[p][1];
    }
  }

  return sum;
}

void part_two(char *input) {
  WSCORE = 21;

  Player players[2];
  parse_inputs(input, players);

  uint64_t wins[2] = {quantum_game((Player[2]){players[0], players[1]}, 0),
                      quantum_game((Player[2]){players[1], players[0]}, 1)};
  printf(
      "Player1 won in %lu universes\n"
      "Player2 won in %lu universes\n"
      "\nSolution : %lu\n",
      wins[0], wins[1], max(wins[0], wins[1]));
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
