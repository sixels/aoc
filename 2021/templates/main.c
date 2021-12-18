#include<stdio.h>
#include<stdlib.h>
#include<assert.h>
#include<string.h>

#if 1
#define INPUT_FILE "./src/#DAY#/sample.txt"
#else
#define INPUT_FILE "./src/#DAY#/inputs.txt"
#endif

void part_one() {
}

void part_two() {
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
