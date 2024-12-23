#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "file_reader.h"

int read_lines(const char* filename, char lines[256][256])
{
    FILE* fp = fopen(filename, "r");
    if (NULL == fp) {
        perror("");
        return 1;
    }

    __ssize_t read = 0;
    size_t length = 0, iterator = 0;
    char* tmp_line = NULL;

    while ((read = getline(&tmp_line, &length, fp)) != -1) {
        if (read && tmp_line[0] != '\n') {
            if (NULL == strncpy(lines[iterator], tmp_line, 255)) {
                perror("");
                return 1;
            }
            if (strlen(tmp_line) >= 256) {
                lines[iterator][255] = '\0';
            } else {
                size_t cur_sz = strlen(lines[iterator]);

                if (lines[iterator][cur_sz - 1] == '\n') {
                    lines[iterator][cur_sz - 1] = '\0';
                }
            }
            iterator++;
        }
    }
    if (iterator < 256) {
        lines[iterator][0] = '\0';
    }

    free(tmp_line);
    fclose(fp);

    return 0;
}