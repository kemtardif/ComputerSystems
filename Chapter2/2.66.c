#include <stdio.h>

/*
* Generate mask indicating leftmost 1 in x. Assume w=32.
* For example, 0xFF00 -> 0x8000, and 0x6600 --> 0x4000.
* If x = 0, then return 0.
*/
int leftmost_one(unsigned x)
{
    /*Now 2 leftmost are 1s for sure*/
    x = x | x >> 1;
     /*Now 4 leftmost are 1s for sure*/
    x = x | x >> 2;
    /*Now 8 leftmost are 1s for sure*/
    x = x | x >> 4;
    /*Now 16 leftmost are 1s for sure*/
    x = x | x >> 8;
    /*Now 32 leftmost are 1s for sure*/
    x = x | x >> 16;    

    /*remove unnessecary ones*/
    x = x ^ (x >> 1);

    return x;
}

