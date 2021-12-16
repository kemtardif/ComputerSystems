/*
Casting to int was done after shifting, so it was logical. Also, shifting should be done 
to the right first, then to the left (so that sign is preserved)
*/

/* Extract byte from word. Return as signed integer */
int xbyte(packed_t word, int bytenum)
{
    int leftShift = (sizeof(int) - 1 - bytenum) << 3
    int rightShift = (sizeof(int) -1) << 3;


    return ((int)word << leftShit >> rightShift) & 0xFF;
};

