#include "show_bytes.h"
#include <stdio.h>

unsigned replace_byte (unsigned x, int i, unsigned char b);

int main(void)
{
    unsigned result = replace_byte(0x12345678, 2, 0xAB);
    unsigned result1 = replace_byte(0x12345678, 0, 0xAB);
    show_unsigned(result1);
}

unsigned replace_byte (unsigned x, int i, unsigned char b)
{
    unsigned mask = ~((unsigned)0xFF << (i*8));
    unsigned d_b = (unsigned)b << (i*8);

    unsigned m_x = x & mask;
    unsigned result = m_x | d_b;

    return result;
}