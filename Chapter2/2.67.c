

/* The following code does not run properly on some machines */
 int bad_int_size_is_32()
  {
    /* Set most significant bit (msb) of 32-bit machine */
    int set_msb = 1 << 31;
    /* Shift past msb of 32-bit word */
    int beyond_msb = 2 << 31;
    /* set_msb is nonzero when word size >= 32
    beyond_msb is zero when word size <= 32 */
    return set_msb && !beyond_msb;
}

/*
A. Shift by amount bigger than word size is not part of C standard, hence we can't 
assume result. On some computer. 1 << 32 gives 1.
B. Modify the code to run properly on any machine for which data type int is
at least 32 bits.
C. Modify the code to run properly on any machine for which data type int is
at least 16 bits.
*/