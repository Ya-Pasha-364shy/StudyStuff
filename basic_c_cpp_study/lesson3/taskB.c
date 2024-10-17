#include <stdio.h>

#define EXIT_SUCCESS 0
#define EXIT_FAILURE 1

/**
 * Description:
 *
 * Написать определение функции cool_memmove, которая
 * повторяет поведение функции memmove из <string.h>
 */

void* cool_strncpy(char* dest, const char* src, unsigned long long bytes)
{
    unsigned long long i = 0;
    for (; i < bytes; i++) {
        dest[i] = src[i];
    }
    return dest;
}

void* cool_memmove(void* dest, const void* src, unsigned long long bytes)
{
    char source[1024] = "";
    (void)cool_strncpy(source, src, bytes);

    char* destination = (char*)dest;
    unsigned long long i = 0;

    for (; i < bytes; i++) {
        *(destination + i) = *(source + i);
    }

    return destination;
}

int main(void)
{
    unsigned char src[10] = "1234567890";

    char* result = cool_memmove(&src[4], &src[3], 3);
    if (!result) {
        return EXIT_FAILURE;
    } else {
        printf("result of memmove: %s\n", src);
        return EXIT_SUCCESS;
    }
}