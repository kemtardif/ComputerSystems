/*
We use the fact that for a given bit-representation, the relationship between the signed
and unsigned values x and x' is x = x' + (highest bit of x') * 2^w. Thus the value of the 
unsigned product x * y in terms of signed x' and y' is (writing x_h for highest bit of x):

x * y = (x' + x_h * 2^w) * (y' + y_h * 2^w) = x'*y' + 2^w*(x_h*y' + y_h*x') + 2^(2*w)*x_h*y_h

The two last terms are terms that are truncated when multiplication is restricted to 
w-bit values, however they are part of the high-order term in the full 2w-bit representation.
Thus if signed_high_prod gives the high-order term of the product x'*y', the unsigned high-order term
is given by adding the above two terms.

*/

int signed_high_prod(int x, int y);

unsigned unsigned_high_prod(unsigned x, unsigned y)
{
    int isXPos = !!(x & INT_MIN);
    int isYPos = !!(y & INT_MIN);

    int middle part = (isXPos * y) + (isYPos * x);
    int highPart = INT_MIN * isXPos * isYPos

    int intHighTerms = signed_high_prod(x1, y1) + middlePart + highPart;

    return (unsigned)intHighTerms;
}