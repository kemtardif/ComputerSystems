/*
A. x in %rdi, n in %ecx, result in %rax, mask in %rdx
B. result is initially 0 and mask is 1
C. mask & mask != 0 i.e. mask not equal to zero
D. mask << n
E. result = result | (x & mask);
F.

    long loop(long x, long n)
    {
        long result = 0;
        long mask;
        for (mask = 1; mask != 0 ; mask = mask << n ) 
        {
            result |= x & mask;
        }
        return result;
    }
*/