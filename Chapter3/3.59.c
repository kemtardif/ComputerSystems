/*

typedef __int128 int128_t;

void store_prod(int128_t *dest, int64_t x, int64_t y)
{
    *dest= x * (int128_t)y;
}

Parameters dest in %rdi, x in %rsi and y in %rdx

The algorithm is that given two 128-bit numbers x and y in the form x = xH * 2^64 + xL and y = yH * 2^64 + yL,
their 128-bit product is given by x * y = [(xH * yH) * 2^128 + (xH * yL + xL * yH) * 2^64 + xL * yL]MOD(2^128)
= [(xH * yL + xL * yH) * 2^64]MOD(2^128) + xL * yL = [xH * yL + xL * yH]MOD(2^64) * 2^64 + xL * yL.
Thus the first term involve only 64-bit numbers operations, while the lower term is a full 128-bit multiplication
of 64-bit numbers.

Using the above novation for x and y, we can annote the code as follow : 

store_prod:
    movq %rdx, %rax // Get 64-bit y in %rax
    cqto // Extend y to 128-bit : yH in %rdx and yL in %rax
    movq %rsi, %rcx // Get 64-bit x in %rcx
    sarq $63, %rcx  // Extend x to 128-bit : xH in %rcx and xL in %rsi
    imulq %rax, %rcx // Quad-* yL and xH in %rcx 
    imulq %rsi, %rdx // Quad-* yH and xL in %rdx
    addq %rdx, %rcx // Add both terms to form upper bytes in $rcx
    mulq %rsi // Fully multiply xL and yL, with upper bytes in %rdx and lower bytes in %rax
    addq %rcx, %rdx // Add all upper byte parts in %rdx
    movq %rax, (%rdi) // Set lower bytes in memory with  %rdi
    movq %rdx, 8(%rdi) // Set upper bytes in memory with address %rdi + 8
    ret

*/