#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ADDR_LEN 16
#define FILE_PATH "/tmp/ip_store"

/**
 * Description:
 *
 * На наш веб-сервис приходят пользователи с
 * разными IP адресами и время от времени необходимо
 * проверять, был ли у нас пользователь с определенным IP адресом.
 * IP адрес задается в формате 255.255.255.255,
 * где каждое число - 0 до 255.
 * Предлагается написать хранилище адресов в файлике
 */

void storeAddrs(unsigned cnt)
{
    FILE* file = fopen(FILE_PATH, "w");
    if (!file) {
        return;
    }
    for (unsigned i = 0; i < cnt; i++) {
        char addr[MAX_ADDR_LEN];
        if (scanf("%15s", addr) != 1) {
            fclose(file);
            return;
        }
        fprintf(file, "%s\n", addr);
    }
    fclose(file);
}

void checkAdds(unsigned cnt)
{
    FILE* file = fopen(FILE_PATH, "r");
    if (!file) {
        return;
    }

    char addr[MAX_ADDR_LEN];
    for (unsigned i = 0; i < cnt; i++) {
        if (scanf("%15s", addr) != 1) {
            fclose(file);
            return;
        }
        short found = 0;
        char line[MAX_ADDR_LEN];
        rewind(file);
        while (fgets(line, sizeof(line), file)) {
            line[strcspn(line, "\n")] = 0;
            if (strcmp(line, addr) == 0) {
                found = 1;
                break;
            }
        }
        printf("%s\n", found ? "yes\n" : "no\n");
    }
    fclose(file);
}

int main()
{
    unsigned cnt;
    if (scanf("%u", &cnt) != 1) {
        return EXIT_FAILURE;
    }
    storeAddrs(cnt);

    if (scanf("%u", &cnt) != 1) {
        return EXIT_FAILURE;
    }
    checkAdds(cnt);

    return 0;
}