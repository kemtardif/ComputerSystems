#include <stdio.h>

typedef unsigned char *byte_pointer;

void show_bytes(byte_pointer x, size_t len);
void show_int(int x);

int main(void)
{
    int x =  0x89ABCDEF;
    int y =  0x76543210;
    int x1 = x & 0xFF; // 0x000000EF
    int y1 = y & ~0xFF; // 0x7654300
    int new = x1 | y1; // so C-expression would be (x & 0xFF) | (y & ~0xFF)

    show_int(new);
}

void show_bytes(byte_pointer x, size_t len)
{
    int i;
    for(i = 0; i < len; i++)
    {
        printf(" %.2x ", x[i]);  
    }
}

void show_int(int x)
{
    show_bytes((byte_pointer)&x, sizeof(int));
}

