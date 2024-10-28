#include <stdio.h>

typedef unsigned int ui;

#define MAX_BUFFER_SZ 256

/**
 * Description:
 *
 * Надо написать функцию my_strncat, которая повторяет поведение
 * функции strncat :)
 * На вход подается две строки, на выходе - две строки,
 * объединненые в одну.
 */

char* my_strncat(char* destination, char* append, ui size)
{
    ui i = 0;
    while (*destination) {
        destination++;
    }

    while (i < size) {
        *(destination + i) = *(append + i);
        ++i;
    }
    *(destination + i) = 0;
    return destination;
}

int main(void)
{
    short n = 0;
    char dest[MAX_BUFFER_SZ] = "";
    char append[MAX_BUFFER_SZ] = "";

    if (scanf("%s", dest) != 1) {
        return -1;
    } else if (scanf("%s", append) != 1) {
        return -1;
    } else if (scanf("%hu", &n) != 1) {
        return -1;
    }
    if (my_strncat(dest, append, n)) {
        printf("%s\n", dest);
    }

    return 0;
}