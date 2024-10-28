/**
 * Description:
 *
 * Реализовать функцию:
 * int cool_strcmp(const char* str1, const char* str2),
 * Функция должна повторять поведение оригинальной strcmp из <string.h>
 */

int cool_strcmp(const char* str1, const char* str2)
{
    while (*str1 && *str2) {
        if (*str1 != *str2) {
            return *str1 > *str2 ? 1 : -1;
        }
        str1++;
        str2++;
    }
    if (*str1)
        return 1;
    if (*str2)
        return -1;

    return 0;
}