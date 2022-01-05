/*
To find the switch values, we look at line 2 and 3 from C code, which subtract 0x3c (60) from n, then
make the unsignecd comparison n - 5 > 0. This tells us that for values not in [60, 65], we jump to
the default case at 4005c3. 

It is then just a matter of looking at the 6 adresses in the jump table, refering to the ordered values 
in [60, 65].
*/

long switch_prob(long x, long n) {
    long result = x;
    switch(n) 
    {
        case 60:
        case 62:
            result *= 8;
            break;
        case 63:
            result >> 3; 
            break;
        case 64:
            x = (x << 4) - x;
        case 65:
            x *= x;
        default:
            result = x + 0x4b;
        break;       
    }
    return result;
}