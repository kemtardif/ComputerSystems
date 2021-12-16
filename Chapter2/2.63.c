#include <stdio.h>
#include <limits.h>
#include "show_bytes.h"

unsigned srl(unsigned x, int k);
int sra(int x, int k);

int main(void)
{
    unsigned result = srl(-1, 8);
    show_unsigned(result);
}
unsigned srl(unsigned x, int k) 
{
    /* Perform shift arithmetically */
    unsigned xsra = (int) x >> k;

    /* Get mask with k 0s and the rest 1s*/
    unsigned mask  = ~(-1 << (8*sizeof(int) - k));

    return xsra & mask;
}

int sra(int x, int k)
{

}