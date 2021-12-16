#include <stdio.h>

int is_little_median()
{
    int x = 1;
    int *y = &x;

    return y[0] == 0x01;
}
