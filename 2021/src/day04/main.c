#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#if 0
#define INPUT_FILE "./src/day04/sample.txt"
#else
#define INPUT_FILE "./src/day04/inputs.txt"
#endif

#define N 5

typedef struct {
  int row[N];
  int len;
} Col;

typedef struct {
  Col cols[N];
  int won;

  int sum;
} Board;

char *read_file() {
  FILE *file = fopen(INPUT_FILE, "r");

  if (file == NULL) {
    fprintf(stderr, "Could not find file %s\n", INPUT_FILE);
    exit(1);
  }

  fseek(file, 0, SEEK_END);
  size_t file_size = ftell(file);
  rewind(file);

  char *content = malloc(file_size + 1);
  fread(content, sizeof(char), file_size, file);

  fclose(file);
  return content;
}

void print_board(Board board) {
  for (int y = 0; y < N; y++) {
    for (int x = 0; x < N; x++) {
      printf("%2d ", board.cols[x].row[y]);
    }
    printf("\n");
  }
}

int next_num(char **input) {
  while (**input < '0' || **input > '9') {
    if (**input == '\0')
      return 0;
    (*input)++;
  }

  char *num_str = *input;
  while (**input >= '0' && **input <= '9')
    (*input)++;

  return atoi(num_str);
}

int win(const Board board) {
  if (board.won) {
    return 0;
  }
  for (int y = 0; y < N; y++) {
    int row = 0;

    for (int x = 0; x < N; x++) {
      if (board.cols[x].len == 0)
        return 1;

      row += board.cols[x].row[y] != -1;
    }

    if (row == 0)
      return 1;
  }

  return 0;
}

void part_one() {
  char *input = read_file();
  char *ptr = input;

  int *draws = calloc(1024, sizeof(int));
  int draws_len = 0;

  // get the drawn numbers
  do {
    int n = next_num(&input);
    draws[draws_len++] = n;
  } while (*input != '\n' && *input != '\0');

  input += 1;

  // 250 boards max
  Board boards[250] = {};

  // get the boards
  int boards_len = 0;
  do {
    for (int i = 0; i < N * N; i++) {
      int n = next_num(&input);

      int x = i % N;
      int y = i / N;
      boards[boards_len].cols[x].row[y] = n;

      if (i == 0) {
        boards[boards_len].cols[x].len = 0;
        boards[boards_len].sum = 0;
      }
      boards[boards_len].cols[x].len++;
      boards[boards_len].sum += n;
    }

    boards_len++;
  } while (*input != '\0');

  for (int i = 0; i < boards_len; i++) {
    print_board(boards[i]);
    printf("\n");
  }

  // the actual problem
  int score = 0, draw = 0;
  for (int d = 0; d < draws_len; d++) {
    draw = draws[d];
    for (int b = 0; b < boards_len - 1; b++) {
      Board *board = &boards[b];

      for (int i = 0; i < N * N; i++) {
        int x = i % N;
        int y = i / N;
        const int value = board->cols[x].row[y];

        if (value != -1 && value == draw) {
          board->sum -= draw;
          board->cols[x].len -= 1;
          board->cols[x].row[y] = -1;
          break;
        }
      }
      printf("========= Board %d  <--- %d\n", b, draw);
      print_board(*board);

      if (win(*board)) {
        printf("board %d won\n", b);
        board->won = 1;
        score = board->sum * draw;
        goto l_end;
      }
    }
  }

l_end:
  printf("Score: %d\n", score);

  free(ptr);
}

void part_two() {
  char *input = read_file();
  char *ptr = input;

  int *draws = calloc(1024, sizeof(int));
  int draws_len = 0;

  // get the drawn numbers
  do {
    int n = next_num(&input);
    draws[draws_len++] = n;
  } while (*input != '\n' && *input != '\0');

  input += 1;

  // 250 boards max
  Board boards[250] = {};

  // get the boards
  int boards_len = 0;
  do {

    for (int i = 0; i < N * N; i++) {
      int n = next_num(&input);

      int x = i % N;
      int y = i / N;
      boards[boards_len].cols[x].row[y] = n;

      if (i == 0) {
        boards[boards_len].cols[x].len = 0;
        boards[boards_len].sum = 0;
      }
      boards[boards_len].cols[x].len++;
      boards[boards_len].sum += n;
    }

    boards_len++;
  } while (*input != '\0');

  for (int i = 0; i < boards_len; i++) {
    print_board(boards[i]);
    printf("\n");
  }

  // the actual problem
  int score = 0, draw = 0, wins = 0;
  for (int d = 0; d < draws_len; d++) {
    draw = draws[d];
    for (int b = 0; b < boards_len - 1; b++) {
      Board *board = &boards[b];

      for (int i = 0; i < N * N; i++) {
        int x = i % N;
        int y = i / N;
        const int value = board->cols[x].row[y];

        if (value != -1 && value == draw) {
          board->sum -= draw;
          board->cols[x].len -= 1;
          board->cols[x].row[y] = -1;
          break;
        }
      }
      printf("========= Board %d  <--- %d\n", b, draw);
      print_board(*board);

      if (win(*board)) {
        wins++;
        board->won = 1;
        if (wins == boards_len - 1) {
          printf("board %d won last\n", b);
          score = board->sum * draw;
          goto l_end;
        }
      }
    }
  }

l_end:
  printf("Score: %d\n", score);

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
