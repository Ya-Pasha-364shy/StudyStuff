#include <stdio.h>
#include <string.h>

#include "file_reader.h"
#include "CMocka_example_sources_B.h"

int count_a(const char *filename) {
    char buf[256] = { 0 };
    unsigned int n = 256;
    int count_a_characters = -1;

    char *line = read_line(buf, n, filename);
    if (line == NULL) {
        return count_a_characters;
    }

    count_a_characters = 0;

    for (size_t i = 0; i < n && line[i] != '\0'; i++) {
        if (line[i] == 'a') {
            count_a_characters++;
        }
    }
    return count_a_characters;
}