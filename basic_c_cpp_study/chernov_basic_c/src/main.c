#include <stdio.h>

#include "sentence_counter.h"

int main(int argc, const char* argv[])
{
    if (argc != 2) {
        fprintf(stderr, "usage: %s [filename]\n", argv[0]);
        return 1;
    }

    char result[256] = { 0 };
    if (longest_sentence_in_file(argv[1], result)) {
        return 1;
    }
    printf("%s\n", result);

    return 0;
}