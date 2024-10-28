#include "stdio.h"
#include "stdlib.h"

#define us unsigned short

#define lineSize 9
#define fieldSize 81
#define threeChunksSize 27

#define is_exists_in_vector(x, bit_vec) (*(us*)bit_vec) & (1 << (x - 1))

#define add_x_to_vector(x, bit_vec) (*(us*)bit_vec) |= (1 << (x - 1))

/**
 * Description:
 *
 * На вход подается матрица 9x9 из цифр от 0 до 9.
 * Надо проверить, является ли эта матрица решенным судоку
 */

// битвектор для допустимых значений на поле брани
typedef struct BV {
    us V1 : 1;
    us V2 : 1;
    us V3 : 1;
    us V4 : 1;
    us V5 : 1;
    us V6 : 1;
    us V7 : 1;
    us V8 : 1;
    us V9 : 1;
} BV, *BV_p;

// создавашка битвектора
BV_p callocBitVector(void)
{
    return (BV_p)calloc(1, sizeof(BV));
}

// зачем чекать каждый чанк если по мере инпута можно сразу три захватить
int scanThreeChunks(us* chunk)
{
    BV_p bit_vec = callocBitVector();
    for (int i = 0; i < lineSize; i += 3) {
        *(us*)bit_vec = 0;
        for (int j = i; j < threeChunksSize - lineSize + i;) {
            us x = chunk[j];
            if (!x || *(us*)bit_vec & (1 << (x - 1))) {
                free(bit_vec);
                return 1;
            } else {
                add_x_to_vector(x, bit_vec);
            }

            if (!((j + 1) % 3)) {
                j += (lineSize - 1);
            } else {
                j++;
            }
        }
    }
    free(bit_vec);
    return 0;
}

// проверка линии на валидность
int scanLines(us* line)
{
    BV_p bit_vec = callocBitVector();
    for (int i = 0; i < lineSize; i++) {
        us x = line[i];
        if (!x || is_exists_in_vector(x, bit_vec)) {
            free(bit_vec);
            return 1;
        } else {
            add_x_to_vector(x, bit_vec);
        }
    }
    free(bit_vec);
    return 0;
}

// просто бегаем по столбцу после полного инита игрового поля
int scanCols(us* field)
{
    BV_p bit_vec = callocBitVector();
    for (int i = 0; i < lineSize; i++) {
        *(us*)bit_vec = 0;
        int col_limit = fieldSize - lineSize * i;
        for (int j = i; j < col_limit; j += 9) {
            us x = field[j];
            if (!x || is_exists_in_vector(x, bit_vec)) {
                free(bit_vec);
                return 1;
            } else {
                add_x_to_vector(x, bit_vec);
            }
        }
    }
    free(bit_vec);
    return 0;
}

int validateSudoku()
{
    us* gameField = (us*)calloc(1, fieldSize * sizeof(us));
    if (!gameField) {
        return EXIT_FAILURE;
    }

    for (us i = 0; i < fieldSize; i++) {
        if (scanf("%hu", gameField + i) != 1) {
            goto fail;
        }
        if (!((i + 1) % 9)) {
            if (scanLines(&gameField[i - 8])) {
                goto fail;
            }
        }
        if (!((i + 1) % 27)) {
            if (scanThreeChunks(&gameField[i - 26])) {
                goto fail;
            }
        }
    }
    if (scanCols(gameField)) {
        goto fail;
    }

    free(gameField);
    printf("valid\n");
    return 0;

fail:
    free(gameField);
    printf("invalid\n");
    return 0;
}

int main()
{
    int res = validateSudoku();
    return res;
}
