/* Inner product with 6x1 loop unrolling */
void inner6x1Loop(vec_ptr u, vec_ptr v, data_t *dest)
{
    long i;
    long length = vec_length(u);
    long limit = length - 5;
    data_t *udata = get_vec_start(u);
    data_t *vdata = get_vec_start(v);
    data_t acc0 = (data_t) 0;
    data_t acc1 = (data_t) 0;
    data_t acc2 = (data_t) 0;
    data_t acc3 = (data_t) 0;
    data_t acc4 = (data_t) 0;
    data_t acc5 = (data_t) 0;

    for (i = 0; i < limit; i+=6)
    {
        acc0 += udata[i] * vdata[i];
        acc1 += udata[i + 1] * vdata[i + 1]; 
        acc2 += udata[i + 2] * vdata[i + 2]; 
        acc3 += udata[i + 3] * vdata[i + 3]; 
        acc4 += udata[i + 4] * vdata[i + 4]; 
        acc5 += udata[i + 5] * vdata[i + 5]; 
    }

    for(; i < length; i++)
    {
        acc0 += udata[i] * vdata[i];
    }

    *dest = acc0 + acc1 + acc2 + acc3 + acc4 + acc5;
}

/*
The throughtput bound give the lowest bound on CPE. This is the issue time  (number of clock cycles a CPU can produce an operation)
divided by the number of functional units that can compute such operations.
*/