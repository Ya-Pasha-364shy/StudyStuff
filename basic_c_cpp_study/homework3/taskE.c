#include <stdio.h>

#include <string.h>

#include <ctype.h>

/**
 * Description:
 *
 * На вход подаются строки, надо найти среди них палиндромы,
 * посчитать, и вывести номера строк-палиндромов.
 * Здесь палиндромом является последовательность одинаковых
 * латинских симолов, поэтому при проверке игнорируем
 * знаки препинания и регистр.
 */

short ispalindrome(char* sentence)
{
    char* left = sentence;
    char* right = sentence + strlen(sentence);
    if (right - left < 3) {
        return 0;
    }

    char* begin = left;
    char* end = right;

    while (left < right) {
        while (!isalnum(*left) && left < end) {
            left++;
        }
        while (!isalnum(*right) && right >= begin) {
            right--;
        }
        if (left >= right) {
            break;
        }

        if (tolower(*left) != tolower(*right)) {
            return 0;
        }

        left++;
        right--;
    }

    return 1;
}

int main()
{
    char buffer[4096];
    int i = -1;
    int palindromes[4096] = {};
    unsigned count = 0;

    while (fgets(buffer, 4096, stdin) != NULL) {
        i++;

        if (ispalindrome(buffer)) {
            palindromes[count++] = i;
        }
    }

    printf("%u\n", count);
    for (unsigned i = 0; i < count; i++) {
        if (count - 1 == i) {
            printf("%d\n", palindromes[i]);
        } else {
            printf("%d ", palindromes[i]);
        }
    }

    return 0;
}