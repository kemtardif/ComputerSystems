/*
A. Any bit of x equals 1 : !!x -- if x has a 1 bit, !x is zero, hence !!x is 1. Conversely,
if x is zero (no 1), then !x is one and !!x is zero.

B. Any bit of x equals 0 : !!(x^~0) -- if x has a 0 bit, then x^~0 must have a 1 bit at the same position,
and by the aboxe !!(x^~0) is one. Conversely, if x has only 1 bits, then x^~0 is 0, and !!(x^~0) is 0.

C. Any bit in the least significant byte of x equals 1 : !!(x&0xFF) : x&0xFF return the least significant byte of x,
and other bytes zeros. We then use part A.

D. Any bit in the most significant byte of x equals 0 : !!((x >> ((sizeof(int) -1) << 3)) | ~0xFF)^~0) : 
    This one is a bit trickier. First, x >> ((sizeof(int) << 3)) shift the most significant byte to the position
    of the least significant. Operating with |~0xFF (which is all bytes 0xFF except for the least significant byte, which is 0x00)
    we get all bytes with 0xFF, but the least significant byte unchanged. Applying ^~0 will then yield all 0x00 bytes, except maybe 
    for the least significant byte. Then if the most significant byte of x contain any zero, so does the least significant byte of 
    the above result, hence we get at at least one one with ^~0, so the above yield 1. Conversely, if there's onle ones in the most significant
    byte of x, ^~0 will yield all zeros in the least significant byte of the aboze, hence the result will be 0.














*/