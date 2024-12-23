#include "file_reader.h"

#include <stdio.h>
#include <string.h>

char* read_line(char* buffer, size_t n, const char* filename) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        return NULL;
    }
    if (fgets(buffer, n, file)) {
        size_t len = strlen(buffer);
        if (len > 0 && buffer[len - 1] == '\n') {
            buffer[len - 1] = '\0';
        }
        fclose(file);
        return buffer;
    }
    fclose(file);
    return NULL; 
}