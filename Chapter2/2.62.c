#include <stdio.h>

int int_shifts_are_arithmetic();

int main()
{
    int result = int_shifts_are_arithmetic();
    printf("%i", result);
}
int int_shifts_are_arithmetic()
{
    return (~0 >> 1) == ~0;
}