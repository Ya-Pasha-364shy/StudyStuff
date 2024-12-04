#ifndef HELLO_HEADER_H
#define HELLO_HEADER_H

#include <stdio.h>

#define EXIT_SUCCESS 0

void my_printf(const char* payload) {
    printf("%s\n", payload);
}

#endif