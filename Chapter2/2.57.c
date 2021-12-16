#include <stdio.h>

typedef unsigned char *byte_pointer;

void show_bytes(byte_pointer x, size_t len);
void show_short(short s);
void show_long(long l);
void show_double(double d);

int main(void)
{
    show_short(12345);
    show_long(12345);
    show_double(12345);
}
void show_bytes(byte_pointer x, size_t len)
{
    int i;
    for(i = 0; i < len; i++)
    {
        printf("%.2x", x[i]);
    }
    printf("\n");
}

void show_short(short s)
{
    show_bytes((byte_pointer)&s, sizeof(short));
}

void show_long(long l)
{
    show_bytes((byte_pointer)&l, sizeof(long));
}

void show_double(double d)
{
    show_bytes((byte_pointer)&d, sizeof(double));
}