 #define K sizeof(unsigned long)
 
 /* Basic implementation of memset */
void *basic_memset0(void *s, int c, size_t n)
{
    size_t cnt = 0;
    unsigned char *schar = s;
    while (cnt < n)
    {
        *schar++ = (unsigned char) c;
        cnt++;
    }
    return s;
}

/*We can first re-write this using  a for loop*/

void *basic_memset1(void *s, int c, size_t n)
{
    size_t cnt;
    unsigned char *schar = s;

    for(cnt = 0; cnt < n; cnt++)
    {
        *schar++ = (unsigned char) c;
    }
}

/*Until the write address is a multiple of K, we want byte-level writes*/

void *basic_memset1(void *s, int c, size_t n)
{
    size_t cnt;

    unsigned char *schar = s;
    unsigned char cChar = (unsigned char) c;

    //////Construction of copies of c in the most genereal way i.e. K can be even or odd.
    unsigned long cLong = (unsigned long)cChar;
    unsigned int temp = 1;
    while(temp != K)
    {
        cLong = cLong | (cLong << 2);
        temp++;
    }

    ///This ensure the write address is K-aligned.
    for(cnt = 0; cnt < n; cnt++)
    {
        if(schar % K == 0) break;
        *schar++ = cChar;
    }

    //At this point, schar is K-aligned. We can then Kx1-unroll the loop: 

    size_t limit = n - K + 1;
    unsigned long * sLong = sChar;

    for(; cnt < limit; cnt+=K)
    {
        *sLong++ = cLong;
    }

    sChar = SLong;
    //We then byte-write the last elements
    for(;cnt < n; cnt++)
    {
        *sChar++ = cChar
    }

    return s;
}