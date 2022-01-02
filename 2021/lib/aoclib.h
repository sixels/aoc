#ifndef AOC_LIB_H
#define AOC_LIB_H

#include <stddef.h>

#define max(a, b) (a < b ? b : a)
#define min(a, b) (a < b ? a : b)


char *read_file(char *);
int next_num(char **);
char *toktok(char **__restrict__ str, char *__restrict__ del);
char *tokntok(char **__restrict__ str, size_t n, char *__restrict__ del);

#define unreachable() assert(((void)"Entered unreachable code: " __FILE__, false))
#define todo() assert(((void)"Not yet implemented: " __FILE__, false))


#endif