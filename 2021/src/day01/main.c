#include<stdio.h>
#include<stdlib.h>
#include<assert.h>
#include<string.h>

#if 0
#define INPUT_FILE "./src/day01/sample.txt"
#else
#define INPUT_FILE "./src/day01/inputs.txt"
#endif

char * read_file() {
    FILE *file = fopen(INPUT_FILE, "r");

    if (file == NULL) {
        fprintf(stderr, "Could not find file %s\n", INPUT_FILE);
        exit(1);
    }

    fseek(file, 0, SEEK_END);
    size_t file_size = ftell(file);
    rewind(file);

    char *content = malloc(file_size+1);
    fread(content, sizeof(char), file_size, file);

    return content;
}

int part_one() {
    char *input = read_file();
    char *ptr = input;

    int offset = 0, last_depth = 0, increased = -1;
    for (char ch = input[0]; ;ch = input[offset]) {
        if (ch == '\n' || ch == '\0') {
            
            const int depth = atoi(input);
            if (depth > last_depth) {
                increased++;
            }
            last_depth = depth;

            input+=offset;
            offset = 0;

            if (ch == '\0') break;
        }
        offset++;
    }
    printf("depth increased %d times\n", increased);

    free(ptr);
    return increased;
}

int next_num(char **input) {
    int offset = 0;
    for (char ch = **input ;; ch = (*input)[offset++]) {
        if (ch == '\n' || ch == '\0') {
            const int depth = atoi(*input);
            *input += offset;
            
            return depth;
        }
    }
}

int part_two() {
    char *input = read_file();
    char *ptr = input;

    int increased = -1;
  

    int last_depth = 0;
    int windows[] = {0,0,0,0};

    // i = 0
    windows[0] = next_num(&input);
    
    // i = 1
    windows[1] = next_num(&input);
    windows[0] += windows[1];

    while(*input != 0) {
        const int depth = next_num(&input);
        if (depth == 0) break;

        windows[2] = depth;
        windows[1] += depth;
        windows[0] += depth;

        if (windows[0] > last_depth) increased++;
        last_depth = windows[0];
        windows[0] = windows[1];
        windows[1] = windows[2];
    };

    printf("depth increased %d times\n", increased);

    free(ptr);
    return increased;
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
