/*
A. We look at lines 4 to 6 in the ASM code, which represent getting the value in memory 
@ address 0x8 + bp + 40*i into %rdx. From line 8, we see that this value is ap->idx. 40 is then 
the size of a_struct, while 8 is the size of bp->first plus a 4 bytes gap so that the a_struct
array in b_struct is 8-aligned. Then from line 1, bp->last has offset 0x120, or 288 = 8 + 40*CNT, 
so that CNT = 7.

B.
typedef struct {
    long idx;
    long x[4];
 } a_struct;
*/