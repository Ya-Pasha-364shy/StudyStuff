#include <stdio.h>

/* needs for cmocka */
#include <setjmp.h>
#include <stddef.h>
#include <stdarg.h>
/* cmocka lib */
#include <cmocka.h>

#include <stdlib.h>

static void a_test_malloc(void **state)
{
    int *memory = malloc(10 * sizeof(int));
    assert_non_null(memory);
    free(memory);
}

/** в любой тест нужно передавать state */
static void null_test_success(void **state)
{
    assert_true(0);
}

int main(void)
{
    const struct CMUnitTest tests[] = {
        cmocka_unit_test(null_test_success),
        cmocka_unit_test(a_test_malloc),
    };

    return cmocka_run_group_tests(tests, 0, 0);
}