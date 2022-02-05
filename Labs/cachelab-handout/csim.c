#include "cachelab.h"
#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <string.h>

int g_Hits = 0;
int g_Miss = 0;
int g_Evictions = 0;


typedef struct cache_ine 
{
    int valid;
    int LRU;
    unsigned long tag;
} cache_line;

void parse(long * sp, long *tp, long * Sp, long * Ep, long * bp, FILE ** fp, int argc, char *argv[]);
void set_cache(cache_line *c, unsigned long *tag, long E);

int main(int argc, char *argv[])
{
    //Cache parameters
    cache_line **cache;
    long s, t, b, S, E;

    //File reading parameters
    FILE *f = NULL;
    char finstr;
    int fdata_size;
    unsigned long fAddr, fset, ftag;
    unsigned long fSMask, fTMask;

    //Loop parameters
    int i, y;

    //Parse CL args
    parse(&s, &t, &S, &E, &b, &f, argc, argv);
    fSMask = (1 << s) - 1;
    fTMask = (1 << t) - 1;

    //Initialize cache
    cache = malloc(sizeof * cache * S);
    if(cache)
    {
        for(i = 0; i < S; i++)
        {      
            cache[i] = malloc(sizeof * cache[i] * E);
            if(cache[i])
            {
                for(y = 0; y < E; y++)
                {
                    cache[i][y].valid = 0;
                    cache[i][y].LRU = 0;
                    cache[i][y].tag = -1 ;                        
                }
            }
            else
            {
                fprintf(stderr, "Error while creating the cache.");
                exit(EXIT_FAILURE);
            }

        }
    }
    else 
    {
        fprintf(stderr, "Error while creating the cache.");
        exit(EXIT_FAILURE);
    }

    //Read file
    while (fscanf(f, " %c %lx,%d", &finstr, &fAddr, &fdata_size) != EOF) {
        if(finstr != 'I')
        { 
            fset = (fAddr >> b) & fSMask;
            ftag = (fAddr >> (s + b)) & fTMask;
            
            set_cache(cache[fset], &ftag, E);
            if(finstr == 'M')
                set_cache(cache[fset], &ftag, E);
        }
    }

    printSummary(g_Hits, g_Miss, g_Evictions);
    for(i = 0; i < S; i++)
    {   
        if(cache[i])
            free(cache[i]);
    }
    free(cache);
    fclose(f);
    return 0;
}

void parse(long *sp, long *tp, long * Sp, long *Ep, long *bp, FILE **fp, int argc, char *argv[])
{
    long c;
    opterr = 0;
    while((c = getopt(argc, argv, "s:E:b:t:")) != -1)
    {
        switch(c)
        {
            case 's':
            *sp = atol(optarg);
            break;
            case 'E':
            *Ep = atol(optarg); 
            break;
            case 'b':
            *bp = atol(optarg);  
            break;
            case 't':
            *fp = fopen(optarg, "r");  
            break;
            default:
            fprintf(stderr, "Usage: %s [-sEbt] \n", argv[0]);
            exit(EXIT_FAILURE);
        }
    }
    if(!*fp)
    {
        fprintf(stderr, "%s : Not a valid file path\n",optarg);
        exit(EXIT_FAILURE);
    }
    if(*Ep == 0)
    {
        fprintf(stderr, "E must be positive.");
        exit(EXIT_FAILURE);
    }

    *tp =     (sizeof(long) << 3)  - *sp - *bp;
    *Sp = 1 << *sp;
    return;
}

void set_cache(cache_line *c, unsigned long * tag, long E)
{
    int i;
    int hit = 0;
    int sat = 1;
    int LRUE;
    unsigned long LRUt;

    //Cache hit
    for(i = 0; i < E; i++)
    {
        if(c[i].valid == 1 && c[i].tag == *tag)
        {

            g_Hits++;
            hit = 1;
            c[i].LRU = 0;
        } 
        else
        {
            c[i].LRU++;
        }
    }

    //Cache miss
    if(hit == 0)
    {
        g_Miss++;
        for(i = 0; i < E; i++)
        {
            if(c[i].valid == 0)
            {
                c[i].valid = 1;
                c[i].LRU = 0;
                c[i].tag = *tag;
                sat = 0;
                break;
            }
        }
        //Eviction
        if(sat == 1)
        {   
            g_Evictions++;
            LRUE = c[0].LRU;
            LRUt = 0;

            for(i = 0; i < E; i++)
            {
                if(c[i].LRU >= LRUE)
                {
                    LRUE = c[i].LRU;
                    LRUt = i;
                }
            }
            c[LRUt].tag = *tag;
            c[LRUt].LRU = 0;
        }
    }    
    return;
}
