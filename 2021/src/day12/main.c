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
#define INPUT_FILE "./src/day12/sample.txt"
#else
#define INPUT_FILE "./src/day12/inputs.txt"
#endif

typedef struct node {
  // names are ranged from a-zA-Z, we will have a maximum of 52 sibling nodes
  // (including Start and End)
  struct node *siblings[55];
  // the actual number of siblings
  size_t siblings_len;

  bool visited;
  bool is_big;
} Graph;

static Graph *nodes[128];

struct node *create_node(bool is_big) {
  struct node *node = malloc(sizeof(struct node));
  *node = (Graph){
      .siblings = {NULL},
      .siblings_len = 0,
      .visited = false,
      .is_big = is_big,
  };
  return node;
}

Graph *node_from_name(char *name, size_t len) {
  Graph *node;
  if (len == 2) {
    node = nodes[(int)name[1]];
    if (!node) {
      node = create_node(name[0] < 'a');
      nodes[(int)name[1]] = node;
    }
  } else {
    node = nodes[len == 3];
  }

  return node;
}

char node_name(Graph *node) {
  if (node)
    for (int i = 'A'; i <= 'z'; i++)
      if (node == nodes[i]) return (char)i;
  return node == nodes[0] ? '^' : '$';
}

// not really necessary, I'm only using it to indent the output
static int visits = 0;

int visit_nodes(Graph *node) {
  int n = 0;
  visits++;

  if (!node || node == nodes[0]) goto end_visit;
  if (node == nodes[1]) {
    n = 1;
    goto end_visit;
  }

  if (node->visited && !node->is_big) goto end_visit;
  node->visited = true;

  for (size_t i = 0; i < node->siblings_len; i++) {
    // Python's string multiplication would be awesome here LOL
    printf("%.*s %c-->%c\n", visits * 2,
           "                                                          ",
           node_name(node), node_name(node->siblings[i]));

    n += visit_nodes(node->siblings[i]);
  }

  node->visited = false;

end_visit:
  visits--;
  return n;
}

void part_one(char *input) {
  Graph *start = create_node(false);
  Graph *end = create_node(false);

  memset(nodes, 0, sizeof(nodes));

  nodes[0] = start;
  nodes[1] = end;

  // parse the inputs
  while (*input) {
    char *from = input;
    while (*input != '-') {
      input++;
    }
    size_t from_len = input - from;
    input++;

    Graph *from_node = node_from_name(from, from_len);

    char *to = input;
    while (*input && *input != '\n') {
      input++;
    }
    size_t to_len = input - to;
    if (*input == '\n') input++;

    Graph *to_node = node_from_name(to, to_len);

    from_node->siblings[from_node->siblings_len++] = to_node;
    to_node->siblings[to_node->siblings_len++] = from_node;
  }

  int n = 0;
  for (size_t i = 0; i < start->siblings_len; i++) {
    printf("%c-->%c\n", node_name(start), node_name(start->siblings[i]));
    n += visit_nodes(start->siblings[i]);
  }

  for (int i = 0; i < 128; i++) {
    if (nodes[i]) free(nodes[i]);
  }

  printf("NUMBER OF PATHS: %d\n", n);
}

int visit_nodes2(Graph *node, int did_small_twice) {
  int n = 0;

  visits++;

  if (!node || node == nodes[0]) goto end_visit2;
  if (node == nodes[1]) {
    n = 1;
    goto end_visit2;
  }

  if (node->visited && !node->is_big) {
    if (did_small_twice) goto end_visit2;
    for (size_t i = 0; i < node->siblings_len; i++) {
      // Python's string multiplication would be awesome here LOL
      // printf("%.*s %c-->%c\n", visits * 2,
      //        "                                                          ",
      //        node_name(node), node_name(node->siblings[i]));

      n += visit_nodes2(node->siblings[i], true);
    }
  } else {
    node->visited = true;

    for (size_t i = 0; i < node->siblings_len; i++) {
      // Python's string multiplication would be awesome here LOL
      // printf("%.*s %c-->%c\n", visits * 2,
      //        "                                                          ",
      //        node_name(node), node_name(node->siblings[i]));

      n += visit_nodes2(node->siblings[i], did_small_twice);
    }
    node->visited = false;
  }

end_visit2:
  visits--;
  return n;
}

void part_two(char *input) {
  Graph *start = create_node(false);
  Graph *end = create_node(false);

  memset(nodes, 0, sizeof(nodes));

  nodes[0] = start;
  nodes[1] = end;

  // parse the inputs
  while (*input) {
    char *from = input;
    while (*input != '-') {
      input++;
    }
    size_t from_len = input - from;
    input++;

    Graph *from_node = node_from_name(from, from_len);

    char *to = input;
    while (*input && *input != '\n') {
      input++;
    }
    size_t to_len = input - to;
    if (*input == '\n') input++;

    Graph *to_node = node_from_name(to, to_len);

    from_node->siblings[from_node->siblings_len++] = to_node;
    to_node->siblings[to_node->siblings_len++] = from_node;
  }

  int n = 0;
  for (size_t i = 0; i < start->siblings_len; i++) {
    printf("%c-->%c\n", node_name(start), node_name(start->siblings[i]));
    n += visit_nodes2(start->siblings[i], false);
  }

  for (int i = 0; i < 128; i++) {
    if (nodes[i]) free(nodes[i]);
  }

  printf("NUMBER OF PATHS: %d\n", n);
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
