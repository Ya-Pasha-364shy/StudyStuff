#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NEW_LINE_SYMBOL "\n"
#define DELIMETER_SYMBOL " "
#define MAX_ARRAY_SZ 1024

void rotate_array(char** array, const size_t sz)
{
    size_t gap = 1;
    for (size_t i = 0; i < sz / 2; i++, gap++) {
        char* tmp = array[i];
        array[i] = array[sz - gap];
        array[sz - gap] = tmp;
    }
}

void print_array(char** array, const size_t sz)
{
    for (size_t i = 0; i < sz; i++) {
        if (sz - i == 1) {
            printf("%s\n", array[i]);
        } else {
            printf("%s ", array[i]);
        }
    }
}

int main()
{
    int N;
    char* array_ptr;
    size_t array_size = 0;
    size_t iterator = 0;
    char* array[MAX_ARRAY_SZ];

    if (scanf("%d", &N) != 1) {
        return -1;
    }
    getchar();

    size_t read_size = getline(&array_ptr, &array_size, stdin);
    if (read_size > MAX_ARRAY_SZ) {
        return -1;
    }
    array_ptr[strcspn(array_ptr, NEW_LINE_SYMBOL)] = 0;

    char* token = strtok(array_ptr, DELIMETER_SYMBOL);
    array[iterator++] = token;
    while (token != NULL) {
        token = strtok(NULL, DELIMETER_SYMBOL);
        array[iterator++] = token;
    }

    rotate_array(array, N);
    print_array(array, N);

    return 0;
}