#include <stdio.h>

/**
 * Description:
 *
 * Написать определение функции cool_memset,
 * которое повторяет поведение оригинальной функции
 * memset из <string.h>
 */

void* cool_memset(void* str, int c, unsigned long long n)
{
    unsigned long long i = 0;
    char* payload = (char*)str;

    for (; i < n; i++) {
        payload[i] = c;
    }

    return payload;
}

int main(void)
{
    char string[] = "Hello";
    printf("%s\n", (char*)cool_memset((void*)string, (int)'1', 5));

    return 0;
}