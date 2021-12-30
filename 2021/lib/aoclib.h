#ifndef AOC_LIB_H
#define AOC_LIB_H

#include <stddef.h>

#define max(a, b) (a < b ? b : a)
#define min(a, b) (a < b ? a : b)


char *read_file(char *);
int next_num(char **);
char *toktok(char **__restrict__ str, char *__restrict__ del);
char *tokntok(char **__restrict__ str, char *__restrict__ del, size_t n);


#endif