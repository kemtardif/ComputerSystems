
void *calloc(size_t nmemb, size_t size)
{
    size_t memSize = nmemb * size;

    if(memSize <= nmemb) 
        return NULL;

    void *add = malloc(memSize);

    add = memset(add, 0, size);

    return add;
};