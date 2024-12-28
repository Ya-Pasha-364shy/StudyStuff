#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int char_to_num(char c)
{
    return (int)c - 48;
}

char num_to_char(int n)
{
    return (char)(n + 48);
}

void sum(char *array1, char *array2, int nums, int maxs)
{
    int a = 0, i, rs = 0;

    for (i = nums; i >= 0; i--) {
        rs = char_to_num(array1[maxs]) + char_to_num(array2[i]) + a;
        if (rs >= 10) {
            a = 1;
            rs %= 10;
        } else {
            a = 0;
        }

        array1[maxs] = num_to_char(rs);
        --maxs;
    }

    for (int j = maxs; j >= 0; j--) {
        rs = char_to_num(array1[j]) + a;

        if (rs >= 10) {
            a = 1;
            rs %= 10;
        } else {
            a = 0;
        }

        array1[j] = num_to_char(rs);
    }
}

// На вход подается число из N цифр (1 <= N < 2000) без ведущих нулей.
// Определить число единиц в двоичной записи этого числа
int count_ones_in_binary(const char *number) {
    int count = 0;
    int len = strlen(number);
    int binary_digit;

    int digits[2000];
    for (int i = 0; i < len; i++) {
        digits[i] = number[i] - '0';
    }

    while (len > 0) {
        binary_digit = 0;
        for (int i = 0; i < len; i++) {
            int current = binary_digit * 10 + digits[i];
            digits[i] = current / 2;
            binary_digit = current % 2;
        }
        if (binary_digit == 1) {
            count++;
        }

        // remove leader zeros
        while (len > 0 && digits[0] == 0) {
            for (int i = 0; i < len - 1; i++) {
                digits[i] = digits[i + 1];
            }
            len--;
        }
    }

    return count;
}

int main(void)
{
    char gap = 'a';
    const char *test_str = "abcdefghia";
    char *string_iterator = (char *)test_str;
    unsigned int vec = 0, iterator = 0, repeated_cnt = 0;

    while (*string_iterator != 0)
    {
        iterator++;
        char current_symbol = *(string_iterator++);
        // в-принципе сдвигов хватит на весь английский алфавит, но не хватит на русский,
        // по-этому для русского языка нужно использовать long int
        unsigned int mask = 1 << (current_symbol - gap);

        if (vec & mask) {
            repeated_cnt++;
        } else {
            vec |= mask;
        }
    }
    printf("number of unique symbols %d in %s\n", iterator - repeated_cnt, test_str);

    char array1[2000] = "699";
    char array2[2000] = "1";
    unsigned int len1 = strlen(array1);
    unsigned int len2 = strlen(array2);

    if (len1 > len2) {
        sum(array1 /* "541" */, array2 /* "9" */, len2 - 1 /* 1 */, len1 - 1/* 3 */);
        printf("result of sum: %s\n", array1);

    } else {
        sum(array2, array1, len1 - 1, len2 - 1);
        printf("result of sum: %s\n", array2);
    }

    printf("%d\n", count_ones_in_binary("1337"));

    return 0;
}
