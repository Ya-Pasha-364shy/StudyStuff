#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "file_reader.h"

int read_lines(const char* filename, char lines[MAX_STR_LENGTH][MAX_STR_LENGTH])
{
    FILE* fp = fopen(filename, "r");
    if (NULL == fp) {
        perror("Unable to open file");
        return 1;
    }

    __ssize_t read = 0;
    size_t length = 0, iterator = 0;
    char* tmp_line = NULL;

    while ((read = getline(&tmp_line, &length, fp)) != -1) {
        if (read && tmp_line[0] != '\n') {
            if (NULL == strncpy(lines[iterator], tmp_line, MAX_STR_LENGTH - 1)) {
                perror("Error when strncpy");
                return 1;
            }

            if (strlen(tmp_line) >= MAX_STR_LENGTH) {
                lines[iterator][MAX_STR_LENGTH - 1] = '\0';
            } else if (lines[iterator][read - 1] == '\n') {
                lines[iterator][read - 1] = '\0';
            }
            iterator++;
        }
    }
    if (iterator < MAX_STR_LENGTH) {
        lines[iterator][0] = '\0';
    }

    free(tmp_line);
    fclose(fp);

    return 0;
}
