#include <stdio.h>

#include <string.h>

#include <ctype.h>

#define MAX_LINES 10
#define MAX_LENGTH 256

/**
 * Description:
 *
 * На вход подаются строки, надо найти среди них палиндромы,
 * посчитать, и вывести номера строк-палиндромов.
 * Здесь палиндромом является последовательность одинаковых
 * латинских симолов, поэтому при проверке игнорируем
 * знаки препинания и регистр.
 */

short is_palindrome(const char* str)
{
    unsigned left = 0;
    unsigned right = strlen(str);

    while (left < right) {
        while (left < right && !isalnum(str[left])) {
            left++;
        }
        while (left < right && !isalnum(str[right])) {
            right--;
        }
        if (left >= right) {
            break;
        }

        if (tolower(str[left]) != tolower(str[right])) {
            return 0;
        }

        left++;
        right--;
    }
    return 1;
}

int main(void)
{
    char lines[MAX_LINES][MAX_LENGTH];
    int palindrome_indexes[MAX_LINES];
    int count = 0;

    for (int i = 0; i < MAX_LINES; i++) {
        if (!fgets(lines[i], MAX_LENGTH, stdin)) {
            break;
        }
        lines[i][strcspn(lines[i], "\n")] = '\0';

        if (is_palindrome(lines[i])) {
            palindrome_indexes[count++] = i;
        }
    }

    printf("%d\n", count);
    for (int i = 0; i < count; i++) {
        printf("%d ", palindrome_indexes[i]);
    }
    printf("\n");

    return 0;
}
