/*
We can decompose the polynomial a0 + a1*x + ... + an*x^n into even and odd parts 
(a0 + a2*x^2 + ... + ) + (a1*x + a3*x^3 + ...). Both parts, can then be written
to use Horner's algorithm : a0 + x^2(a2 + x^2(a4 + ... + x^2*a2M)) + 
                            x*(a1 + x^2(a3 + ... + x^2 * a2m-1)...)

This allow to unroll a 2x2a loop unrolling, to which some tweakings must be added to account
for parity.

We could add accumulators, which would avoid computations of product of x up to the number of accumulators.
*/

double polyh1(double a[], double x, long degree)
{
    long i;
    double acc0 = a[degree];
    double acc1 = 0;
    int parity = degree % 2 == 0;
    long end = parity ? 0 : 1;
    double square = x*x;

    for (i = degree; i > end; i-=2)
    {
        acc0 = a[i -2] + square*acc0;
        acc1 = a[i -1] + square*acc1;
    } 

    return parity ? acc0 + x*acc1 : acc0 * x + acc1 + a[0];
}