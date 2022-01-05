/*
    This problem involve looking at the data alignment of the struct elements.
    Looking at line 2 and 3 of the ASM code, we see that q->t and q->u are at adresses
    %rsi + 8 and %rsi + 32, respectively.
    From line 7 of the C code, the above implies that B plus any non-negative gap must equal
    8. Moreover, since t is 4-aligned, B must be greater than 4 (otherwise, B plus any non-negative
    gap would total 4). It follows that 4 < B <= 8.
    Similary, we have that 12 + 2*A plus any non-negative gap must equal 32 from the above. Since u
    is 8-aligned, 12 + 2*A must be greater than 24 (otherwise, 12 + 2*A plus any non-negative gap would total
    24). It follows that 24 < 12 + 2*A <= 32, or 6 < A <= 10.
    From line 4 of the ASM code, 4*A*B + any non-negative gap must equal 184, and since y is 8-aligned, 4*AB must
    be above 176. It follows that 44 < AB <= 46.

    From those inequalities, we can find the appropriate values for A and B by elimination.





    

*/