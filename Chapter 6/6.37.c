/*
A 4-KB (4096) direct-access cache with 16-byte blocks has 256 sets and can hold 1024 elements.
For N = 64, the array has 4096 elements, and the cache can hold 1024 items. Now if a[i, j] is
in a given set, then a[i + 4, j] is also read from that set, so that miss rate is 100%.
For N = 60, the elements are not aligned as such, hence allow for a lower miss rate in SumB of 25%.

For both case, the miss rate in sumA is 25%, which is expected for stride-1 iteration with
four elements per set. The miss rate for sumC is also 25% : we see that 50% are read hit, but 
we are iterating over half the number of elements, hence 50% /2 = 25%.
*/