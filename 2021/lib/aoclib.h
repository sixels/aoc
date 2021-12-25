#ifndef AOC_LIB_H
#define AOC_LIB_H

#define max(a, b) a < b ? b : a
#define min(a, b) a < b ? a : b

char *read_file(char *);
int next_num(char **);
char *toktok(char **str, char *del);


#endif