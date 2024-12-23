#include <stdio.h>
#include <assert.h>

int add(int a, int b)
{
    return a + b;
}

int main(void)
{
    {
        int a = 1;
        int b = 2;
        assert((a + b) == 3 && "first test");
    }
    {
        int a = 1;
        int b = 2;
        assert((a + b) == 1 && "second test");
    }

    return 0;
}