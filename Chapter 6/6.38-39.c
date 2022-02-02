/* 6.38
A. There is 4 writes per iteration, hence 4 * 16 * 16 = 1025 writes.
B. When square[i][j].c is loaded in the cache, the whole structure is 
loaded in the same set. hence the three other writes are write hits,
so that we have 3*16*16 = 768
C. 75%
*/


/* 6.39
A. Same as 6.38, 1025 writes;
b.The first 16 iteration will all be misses, but the next 3 * 16 will be hit.
so again 768.
C. 75%
*/