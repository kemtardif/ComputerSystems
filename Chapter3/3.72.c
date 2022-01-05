/*

A. In line 5, 30 + 8*n byte is allocated on the stack : 30 "free" bytes,
    plus 8*n for each 8 bytes element of the array. On line 6, and-ing with 
    -16 i.e. [10000] in binary set the least 4 bits to zero. This make the 
    allocated space a multiple of 16.
B. On line 8 and 9, we set the address of the first element of p @ %rsp + 15,
    and-ing with -16, making sure it is a multiple of 16.
C.
D. S2 is a multiple of 16, while p is 16 aligned.
*/