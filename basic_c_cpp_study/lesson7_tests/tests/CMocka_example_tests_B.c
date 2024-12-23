#include <stdio.h>

/* needs for cmocka */
#include <setjmp.h>
#include <stddef.h>
#include <stdarg.h>
/* cmocka lib */
#include <cmocka.h>

#include <stdlib.h>
#include <string.h>

#include "CMocka_example_sources_B.h"

#define UNUSED(x) (void)(x)

const char *withACharFileName = "CMocka_example_B1.txt";
const char *withoutACharFileName = "CMocka_example_B2.txt";
const char *invalidFileName = "invalidFileName.txt";

// при компиляции с -Wl,--wrap=read_line все вызовы read_line -> __wrap_read_line
const char *__wrap_read_line(char *buffer, unsigned int n, const char *filename)
{
    UNUSED(n);
    UNUSED(buffer);
    UNUSED(filename);

    // mock_type извлекает значение из очереди, которую задаёт will_return
    // таким образом мы изолируем исполнение функции read_line внутри count_a
    const char *mocked_result = mock_type(const char *);
    return mocked_result;
}

static void a_test_invalid_file(void **state)
{
    UNUSED(state);

    // Функция read_line возвращает NULL для несуществующего файла
    will_return(__wrap_read_line, NULL);

    // count_a будет под собой вызывать __wrap_read_line за место read_line
    int actualRes = count_a(invalidFileName);
    int expectedRes = -1;

    assert_int_equal(actualRes, expectedRes);
}

static void a_test_valid_file_with_a(void **state)
{
    UNUSED(state);

    // Функция read_line возвращает строку с буквами 'a'
    will_return(__wrap_read_line, "aaa bbb ccc aaa ddd eee ff");

    int actualRes = count_a(withACharFileName);
    int expectedRes = 6;

    assert_int_equal(actualRes, expectedRes);
}

static void a_test_valid_file_without_a(void **state)
{
    UNUSED(state);

    // Функция read_line возвращает строку без букв 'a'
    will_return(__wrap_read_line, "bbb ccc ddd eee ff");

    int actualRes = count_a(withoutACharFileName);
    int expectedRes = 0;

    assert_int_equal(actualRes, expectedRes);
}

int main(void)
{
    const struct CMUnitTest tests[] = {
        cmocka_unit_test(a_test_invalid_file),
        cmocka_unit_test(a_test_valid_file_with_a),
        cmocka_unit_test(a_test_valid_file_without_a),
    };

    return cmocka_run_group_tests(tests, 0, 0);
}