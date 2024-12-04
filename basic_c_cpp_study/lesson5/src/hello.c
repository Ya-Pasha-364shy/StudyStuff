#include "hello.h"

extern void my_printf(const char*);

int main(void) {
    my_printf("Hello, world !!!");
    return EXIT_SUCCESS;
}