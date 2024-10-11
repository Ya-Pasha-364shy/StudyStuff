#include <stdio.h>

#include <ctype.h>

#define EXIT_SUCCESS 0
#define EXIT_FAILURE 1
#define MAX_BUFF_SZ 25

/**
 * Description:
 *
 * Дан файл lines.txt, состоящий из новых предложений.
 * Напишите программу, которая подсчитывает и выводит число
 * вхождений каждого символа, игнорируя регистр.
 */

int main(void)
{
    FILE* fp = fopen("lines.txt", "r");
    if (!fp) {
        perror("Error when opening a file: ");
        return EXIT_FAILURE;
    }

    char chr = 0;
    const int offset = (int)'a';
    int hash[MAX_BUFF_SZ + 1] = { 0 };

    while ((chr = fgetc(fp)) != EOF) {
        if (isalpha(chr)) {
            if (!islower(chr)) {
                chr = tolower(chr);
            }
            hash[(int)chr - offset]++;
        }
    }
    for (int i = 0; i <= MAX_BUFF_SZ; i++) {
        printf("%c: %d\n", (char)(i + offset), hash[i]);
    }

    fclose(fp);
    return EXIT_SUCCESS;
}