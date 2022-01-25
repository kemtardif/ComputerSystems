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
        sum = sum + (udata[i] * vdata[i]);
        sum = sum + (udata[i + 1] * vdata[i + 1]);
        sum = sum + (udata[i + 2] * vdata[i + 2]);
        sum = sum + (udata[i + 3] * vdata[i + 3]);
        sum = sum + (udata[i + 4] * vdata[i + 4]);
        sum = sum + (udata[i + 5] * vdata[i + 5]);

    }

    for(; i < length; i++)
    {
        sum  = sum +  (udata[i] * vdata[i]);
    }

    *dest = sum;
}