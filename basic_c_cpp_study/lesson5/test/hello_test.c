#include "hello.h"

extern void my_printf(const char* payload);

int main(void) {

    my_printf("Test's hello world !");
    return EXIT_SUCCESS;
}