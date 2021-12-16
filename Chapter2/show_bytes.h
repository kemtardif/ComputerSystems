#include <stdio.h>

typedef unsigned char *byte_pointer;

void show_bytes(byte_pointer x, size_t len)
{
    int i;
    for(i = 0; i < len; i ++)
    {
        printf("%.2x", x[i]);
        printf("\n");
    }
}
void show_unsigned(unsigned x)
{
    show_bytes((byte_pointer)&x, sizeof(int));
}

void show_int(int x)
{
    show_bytes((byte_pointer)&x, sizeof(int));
}

void show_float(int x)
{
    show_bytes((byte_pointer)&x, sizeof(float));
}
