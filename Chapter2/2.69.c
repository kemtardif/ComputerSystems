
unsigned rotate_left(unsigned x, int n)
{
    unsigned temp = x >> (((sizeof(int) << 3) -1) -n);
    temp = temp >> 1;
    x = x << n;

    return x | temp;
}