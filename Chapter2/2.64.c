#include <stdio.h>

/* Return 1 when any odd bit of x equals 1; 0 otherwise.
Assume w=32 */
int any_odd_one(unsigned x);

int any_odd_one(unsigned x)
{
    int oddBits = 0x55555555;

    return !!(oddBits & (int)x);
}