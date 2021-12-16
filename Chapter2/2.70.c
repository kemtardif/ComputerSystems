#include <stdio.h>
#include "show_bytes.h"

int fits_bits(int x, int n);

/*
Truncating a number to n-bits, it is preserved if, when returning 
to the initial w-bit the value is preserved.
*/
int fits_bits(int x, int n)
{
    int w = sizeof(int) << 3;
    int trunc = x << (w - n);

    trunc = trunc >> (w - n);

    return x == trunc;
}