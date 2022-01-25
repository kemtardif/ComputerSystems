/* Inner product with 6x1 loop unrolling */
void inner6x1Loop(vec_ptr u, vec_ptr v, data_t *dest)
{
    long i;
    long length = vec_length(u);
    long limit = length - 5;
    data_t *udata = get_vec_start(u);
    data_t *vdata = get_vec_start(v);
    data_t sum = (data_t) 0;

    for (i = 0; i < limit; i+=6)
    {
        data_t toAdd = udata[i] * vdata[i];
        toAdd += udata[i + 1] * vdata[i + 1] 
        toAdd += udata[i + 2] * vdata[i + 2] 
        toAdd += udata[i + 3] * vdata[i + 3] 
        toAdd += udata[i + 4] * vdata[i + 4] 
        toAdd += udata[i + 5] * vdata[i + 5] 

        sum = sum + toAdd;
    }

    for(; i < length; i++)
    {
        sum = sum + udata[i] * vdata[i];
    }

    *dest = sum;
}

/*
A. The operation on line 20 is on the critical path, since it is needed to calculate the next iteration.
The toAdd variable can be calculated in advance for out-of-order processors. Thus if we were to completely
unroll the loop, we'd still have to go throught all those addition latencies times the number of additions.
Hence we can't go lower than a CPE of 1.0

B) For floating-point number, the CPE is already around the lowest bound of 3.0, which is the lower bound
for sequential sums if we were to completely unroll the loop.
*/