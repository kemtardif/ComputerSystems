/*

int x = random();
int y = random();

unsigned ux = (unsigned) x;
unsigned uy = (unsigned) y;
*/


/*

A. (x<y) == (-x>-y) : False fot x = INT_MIN and y = 1
B. ((x+y)<<4) + y-x == 17*y+15*x : true, by using 17*y = (y << 4) + y and 15*x = (x << 4) - x
C. ~x+~y+1 == ~(x+y) : true, since using x + ~x = -1 yield equality on both sides.
D. (ux-uy) == -(unsigned)(y-x)
E. ((x >> 2) << 2) <= x : true : x >> 2 is equivalen to dividing by 4, rounding DOWN.
*/

