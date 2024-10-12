#include <stdio.h>

#include <string.h>

typedef unsigned int ui;
typedef unsigned short us;

#define EXIT_SUCCESS 0
#define EXIT_FAILURE 1

/**
 * Description:
 *
 * Сгенерируйте сбалансированные комбинарции скобок.
 * Выведите в порядке обратном лексиграфическому.
 *
 * Пример:
 * 2
 * {}{}
 * {{}}
 *
 * Ограничения:
 * 1<=n<=9
 */

void printParanthes(ui bitmap, us n)
{
    for (us i = n * 2; i != 0; i--, bitmap >>= 1) {
        printf("%c", bitmap & 1 ? '{' : '}');
    }
    printf("\n");
}

void generateParenthesBalanced(us n, us open_cnt, us closed_cnt, ui bitmap, us counter)
{
    if (closed_cnt == n) {
        printParanthes(bitmap, n);
        return;
    }

    if (closed_cnt < open_cnt) {
        generateParenthesBalanced(n, open_cnt, closed_cnt + 1, bitmap, counter + 1);
    }
    if (open_cnt < n) {
        bitmap |= (1 << counter);
        generateParenthesBalanced(n, open_cnt + 1, closed_cnt, bitmap, counter + 1);
    }
    return;
}

int main()
{
    us n;
    if (scanf("%hu", &n) != 1) {
        return EXIT_FAILURE;
    }

    generateParenthesBalanced(n, 0, 0, 0, 0);
    return EXIT_SUCCESS;
}