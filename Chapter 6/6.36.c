/*
A. For a 512-byte cache, there is 32 sets of 16-byte blocks. The cache can hold hold half the array,
hence for each multiplication, both sides are read from the same set, missing everytime.

B.Doubling the cache size allows to hold the whole array. Since each sets hold 4 contiguous array elements,
each read miss entails 3 hits. Hence the miss rate is 25%.

C. As for A, both sides of each multiplication are read from the same sets. However, both values can be cached 
simultaneously, so the miss rate is the same as for B : 25%.

D. No, since the cache already hold the whole array. The second element in each sets would simply be read from 
another set.

E. Yes, since for the same cache size, a larger block size would allow more contiguous reads.

*/