#include <stdio.h>
#include <stdlib.h>
#include "file_reader.h"

void readFromFile(const char *filename) {
    FILE *file = fopen(filename, "r");

    if (file == NULL) {
        perror("Failed to open file for reading");
        return;
    }

    char *line = NULL;
    size_t len = 0;

    while (getline(&line, &len, file) != -1) {
        printf("%s", line); 
    }

    if (line) {
        free(line);
    }

    fclose(file);
}