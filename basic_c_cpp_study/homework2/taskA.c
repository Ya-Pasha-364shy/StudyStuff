#include <stdio.h>

typedef unsigned int ui;

/**
 * Описание:
 *
 * Есть numBottles бутылок с водой (полных). Вы можете обменять numExchange пустых бутылок с водой на одну полную бутылку с водой. Выпивая полную бутылку с водой, вы получаете пустую бутылку.
 * На вход подаются целые числа numBottles и numExchange (через пробел),
 * выведите маскимальное число бутылок с водой, которые вы сможете выпить.
 * Ограничения:
 * 0 <= numBottles <= 100
 * 2 <= numExchange <= 100
 */

int main()
{
    ui numBottles, numExchange;
    if (scanf("%u %u", &numBottles, &numExchange) != 2) {
        return -1;
    }
    getchar();

    ui answer = 0;
    ui emptyBottles = 0;

    while (numBottles > 0) {
        answer += numBottles;
        emptyBottles += numBottles;
        numBottles = emptyBottles / numExchange;
        emptyBottles = emptyBottles % numExchange;
    }

    printf("%u\n", answer);
    return 0;
}