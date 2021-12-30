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
#define INPUT_FILE "./src/day18/sample.txt"
#else
#define INPUT_FILE "./src/day18/inputs.txt"
#endif

enum action {
  EXPLODE,
  SPLIT,
};

struct node {
  bool is_pair;
  uint64_t value;
  struct node *left, *right, *parent;
};

// keep track of all nodes to avoid memory allocation
#define MAX_NODES 15000
static struct node nodes[MAX_NODES];
static size_t nodes_len = 0;

typedef struct {
  char *str;
  int len;
} String;

void json_tree();
void inline_tree();

struct node *new_node(uint64_t value, bool is_pair) {
  struct node node = (struct node){.value = value,
                                   .left = NULL,
                                   .right = NULL,
                                   .parent = NULL,
                                   .is_pair = is_pair};

  int i = nodes_len;
  nodes[i] = node;
  nodes_len = (nodes_len + 1) % MAX_NODES;

  return &nodes[i];
}

#define is_pair(value) (value[0] == '[')
#define is_literal(value) (!is_pair(value))

int pair_len(char *input, int input_len) {
  int depth = 0;

  int len = 0;
  do {
    if (input[len] == '[') depth++;
    if (input[len] == ']') depth--;
    len++;
  } while (depth > 0 && input_len > len);

  return len;
}

char *pair(char *input, int *len, String *left, String *right) {
  char *_left = input;
  int left_len = pair_len(input, *len);
  *left = (String){.str = _left, .len = left_len};
  input += left_len + 1;
  *len -= left_len + 1;

  char *_right = input;
  int right_len = pair_len(input, *len);
  *right = (String){.str = _right, .len = right_len};
  input += right_len;
  *len -= right_len;

  return input;
}

struct node *parse_pairs(char *input, int input_len) {
  String left, right;
  input = pair(input, &input_len, &left, &right);

  struct node *root = new_node(0, true);
  root->left = is_pair(left.str) ? parse_pairs(left.str + 1, left.len - 1)
                                 : new_node(atoi(left.str), false);
  root->right = is_pair(right.str) ? parse_pairs(right.str + 1, right.len - 1)
                                   : new_node(atoi(right.str), false);

  root->left->parent = root;
  root->right->parent = root;

  return root;
}

struct node *prev_left(struct node *node) {
  if (!node) return NULL;

  struct node *aux, *prev = node;
  for (aux = node->parent; aux; aux = aux->parent) {
    if (aux->left && aux->left != prev) break;
    prev = aux;
  }

  if (aux)
    for (aux = aux->left; aux; aux = aux->right ? aux->right : aux->left)
      if (!aux->is_pair) {
        return aux;
      }

  return NULL;
}
struct node *next_right(struct node *node) {
  if (!node) return NULL;

  struct node *aux, *prev = node;
  for (aux = node->parent; aux; aux = aux->parent) {
    if (aux->right && aux->right != prev) break;
    prev = aux;
  }

  if (aux)
    for (aux = aux->right; aux; aux = aux->left ? aux->left : aux->right)
      if (!aux->is_pair) {
        return aux;
      }

  return NULL;
}

void explode(struct node *node);
void split(struct node *node);

void explode(struct node *node) {
  if (!node) return;

  uint64_t lval = node->left->value;
  uint64_t rval = node->right->value;
  // printf("🧨 Exploding [%ld,%ld]\n", lval, rval);

  struct node *pleft, *nright;
  if ((pleft = prev_left(node))) {
    // printf("Left explosion: %ld + %ld\n", pleft->value, lval);
    pleft->value += lval;
  }

  if ((nright = next_right(node))) {
    // printf("Right explosion: %ld + %ld\n", nright->value, rval);
    nright->value += rval;
  }

  // struct node *tmp = new_node(0, false);
  // tmp->parent = node->parent;
  // *node = *tmp;
  node->is_pair = false;
  node->left = NULL;
  node->right = NULL;
  node->value = 0;
}

void split(struct node *node) {
  if (!node) return;

  uint64_t v = node->value;

  // printf("🔪 Splitting %ld\n", v);

  uint64_t lval = v / 2;
  // printf("Left split: %ld\n", lval);
  uint64_t rval = (uint64_t)ceil((double)v / (double)2.0);
  // printf("Right split: %ld\n", rval);

  // struct node *tmp = new_node(0, true);
  // tmp->left = new_node(lval, false);
  // tmp->right = new_node(rval, false);
  // tmp->parent = node->parent;
  // *node = *tmp;
  node->is_pair = true;
  node->value = 0;
  node->left = new_node(lval, false);
  node->right = new_node(rval, false);
  node->left->parent = node;
  node->right->parent = node;
}

#define check_explode(root, depth)                                \
  (root->is_pair && depth == 4 && root->left->is_pair == false && \
   root->right->is_pair == false)

bool reduce(struct node *root, uint64_t depth, enum action action) {
  if (!root) return false;

  if (action == SPLIT && !root->is_pair && root->value >= 10) {
    split(root);
    if (check_explode(root, depth)) {
      explode(root);
    }

    return true;
  }
  if (action == EXPLODE && check_explode(root, depth)) {
    explode(root);
    return true;
  }

  // stop on the first action
  if (reduce(root->left, depth + 1, action)) return true;
  if (reduce(root->right, depth + 1, action)) return true;

  return false;
}

struct node *add(struct node *a, struct node *b) {
  struct node *root = new_node(0, true);
  root->left = a;
  root->left->parent = root;
  root->right = b;
  root->right->parent = root;

  while (reduce(root, 0, EXPLODE)) {
  }
  while (reduce(root, 0, SPLIT)) {
  }

  return root;
}

uint64_t calc_magnitude(struct node *root) {
  if (!root) return 0;

  if (root->is_pair && !root->left->is_pair && !root->right->is_pair) {
    return 3 * root->left->value + 2 * root->right->value;
  } else if (!root->is_pair) {
    return root->value;
  }

  uint64_t lval = calc_magnitude(root->left);
  uint64_t rval = calc_magnitude(root->right);

  return 3 * lval + 2 * rval;
}

void part_one(char *input) {
  char *line = toktok(&input, "\n") + 1;
  int line_len = input - line - 2;

  struct node *result = parse_pairs(line, line_len);

  while (*input && *(input - 1)) {
    char *lines = toktok(&input, "\n") + 1;
    int lines_len = input - lines - 2;

    struct node *b = parse_pairs(lines, lines_len);

    // printf("   ");
    // inline_tree(result);
    // printf("\n+  ");
    // inline_tree(b);

    // printf("\n");
    result = add(result, b);
    // printf("\n=  ");
    // inline_tree(result);
    // printf("\n\n");
  }
  inline_tree(result);
  printf("\nResult = %ld\n", calc_magnitude(result));
  // json_tree(result);
}

void part_two(char *input) {
  String lines[200];
  int lines_len = 0;

  uint64_t max_mag = 0;

  do {
    char *line = toktok(&input, "\n") + 1;
    int line_len = input - line - 2;

    lines[lines_len++] = (String){.str = line, .len = line_len};
  } while (*input && *(input - 1));

  for (int i = 0; i < lines_len - 1; i++) {
    for (int j = 1; j < lines_len; j++) {
      {
        struct node *a = parse_pairs(lines[i].str, lines[i].len);
        struct node *b = parse_pairs(lines[j].str, lines[j].len);

        uint64_t mag = calc_magnitude(add(a, b));
        max_mag = max(mag, max_mag);
      }
      {
        struct node *a = parse_pairs(lines[i].str, lines[i].len);
        struct node *b = parse_pairs(lines[j].str, lines[j].len);

        uint64_t mag = calc_magnitude(add(b, a));
        max_mag = max(mag, max_mag);
      }
    }
  }

  printf("Max magnitude = %ld\n", max_mag);
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

void json_tree_rec(struct node *node, uint64_t depth) {
  if (!node) return;

  printf("{ \"depth\": \"%lu\",", depth);
  printf(" \"pointer\": \"%p\",", node);
  printf(" \"left_pointer\": \"%p\",", node->left);
  printf(" \"right_pointer\": \"%p\",", node->right);
  printf(" \"parent\": \"%p\",", node->parent);
  printf(" \"val\": \"%lu\" ", node->value);

  if (node->left) {
    printf(",\"left\":");
    json_tree_rec(node->left, depth + 1);
  }
  if (node->right) {
    printf(", \"right\":");
    json_tree_rec(node->right, depth + 1);
  }
  printf(" }");
}
void json_tree(struct node *root) {
  printf("[ ");
  json_tree_rec(root, 0);
  printf("]\n");
}

void inline_tree(struct node *node) {
  if (!node) return;

  if (node->is_pair) printf("[");

  if (node->left && !node->left->is_pair)
    printf("%ld", node->left->value);
  else
    inline_tree(node->left);

  if (node->right && !node->right->is_pair)
    printf(",%ld", node->right->value);
  else {
    printf(",");
    inline_tree(node->right);
  }

  if (node->is_pair) printf("]");
}