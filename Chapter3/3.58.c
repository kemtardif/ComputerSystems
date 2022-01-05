/*
long decode2(long x, long y, long z);
Parameters x in %rdi, y in %rsi, and z in %rdx

decode2:
    subq %rdx, %rsi  // y -= z;
    imulq %rsi, %rdi // x *= y;
    movq %rsi, %rax  // return value is set to y;
    salq $63, %rax   // y >> 63;
    sarq $63, %rax   // y << 63;
    xorq %rdi, %rax  // y ^= x;
    ret

*/

long decode2(long x, long y, long z)
{
    long temp0 = y - z;
    long temp1 = x * temp0;

    temp0 >> 63 << 63;
    return temp0 ^ temp1;
}