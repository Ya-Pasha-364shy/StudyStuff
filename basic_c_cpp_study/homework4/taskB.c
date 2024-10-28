/**
 * Description:
 *
 * Реализовать функцию:
 * int cool_strstr(const char* str1, const char* str2),
 * Функция должна повторять поведение оригинальной strcmp из <string.h>
 */


const char* cool_strstr(const char* str1, const char* str2) {
    if (*str2 == '\0') {
        return str1;
    }

    while (*str1) {
        const char* p1 = str1;
        const char* p2 = str2;

        while (*p2 && (*p1 == *p2)) {
            p1++;
            p2++;
        }

        if (*p2 == '\0') {
            return str1;
        }

        str1++;
    }

    return 0;
}
