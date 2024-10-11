#include <stdio.h>

#include <stdlib.h>

typedef unsigned int ui;

/**
 * Description:
 *
 * На вход подается число n.
 * Нарисуйте лестницу высотой n, используя для этого не более n вызовов printf.
 * Подъем по лестнице проходит слева направо, длины соседних ступеней отличаются на 1.
 * Лестница рисуется с помощью единиц, свободное пространство заполняется нулями.
 */

int main()
{
    int offset = -1;
    ui n = 0;
    if (scanf("%u", &n) != 1) {
        return EXIT_FAILURE;
    }

    for (ui i = 0; i < n; i++) {
        char line[21] = "";
        char* line_p = line;
        for (ui j = 1; j <= n; j++) {
            offset = sprintf(line_p, "%c", n - j <= i ? '1' : '0');
            if (offset > 0) {
                line_p += offset;
            } else {
                perror("");
            }
        }
        printf("%s\n", line);
    }

    return EXIT_SUCCESS;
}