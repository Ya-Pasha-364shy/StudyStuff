#include <stdio.h>

#include <stdlib.h>

typedef unsigned int ui;

/**
 * Description:
 *
 * На вход подается число n. Проверьте, является
 * ли его двоичное представление палиндромом.
 * Выведите true, если является, false - в противном случае
 */

int main()
{
    ui n;
    if (scanf("%u", &n) != 1) {
        return EXIT_FAILURE;
    }

    ui n1 = n & 0xFFFF;
    ui n2 = (n & 0xFFFF0000) >> 16;
    ui n2_low = n2 & 0xFF;
    ui n2_high = n2 & 0xFF00;

    ui first_byte = 0, second_byte = 0;
    for (int i = 0; i < 8; i++) {
        if (n2_high & (1 << (i + 8))) {
            first_byte |= (1 << (7 - i));
        }

        if (n2_low & (1 << i)) {
            second_byte |= (1 << (15 - i));
        }
    }
    n2 = second_byte | first_byte;

    printf("%s\n", n1 == n2 ? "true" : "false");
    return EXIT_SUCCESS;
}