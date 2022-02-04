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
    int tag;
} cache_line;

void parse(int * sp, int *tp, int * Sp, int * Ep, int * bp, FILE ** fp, int argc, char *argv[]);

int main(int argc, char *argv[])
{
    //Cache parameters
    cache_line **cache;
    int s, t, b, S, E;//, B;

    //File reading parameters
    FILE *f = NULL;
    char finstr;
    int fdata_size, fAddr;
    unsigned int fset, ftag;

    //Loop parameters
    int i, y;
    //First parse the command-line arguments
    parse(&s, &t, &S, &E, &b, &f, argc, argv);

    //Initialize cache with given values
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
                    cache[i][y].tag = -1;                        
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
    while (fscanf(f, " %c %x,%d", &finstr, &fAddr, &fdata_size) > 0) {
        if(finstr != 'I')
        {
            fset = ((unsigned int)fAddr << t) >> (t + b);
            ftag = (unsigned int)fAddr >> (s + b);
            printf("ADDRESS : %i \n", fAddr);
            printf("TAG : %u \n", ftag);
            printf("SET : %u \n", fset);
           //cache[fset]
          // SetCache(&currentSet, ftag, flines[1]);

        }
    }

    //printSummary(g_Hits, g_Miss, g_Evictions);
    for(i = 0; i < S; i++)
    {   
        if(cache[i])
            free(cache[i]);
    }
    free(cache);
    fclose(f);
    return 0;
}

void parse(int *sp, int *tp, int * Sp, int *Ep, int *bp, FILE **fp, int argc, char *argv[])
{
    long c;
    opterr = 0;
    while((c = getopt(argc, argv, "s:E:b:t:")) != -1)
    {
        switch(c)
        {
            case 's':
            *sp = atoi(optarg);
            break;
            case 'E':
            *Ep = atoi(optarg); 
            break;
            case 'b':
            *bp = atoi(optarg);  
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

    *tp =     8 * sizeof(int) - *sp - *bp;
    *Sp = 1 << *sp;
    return;
}

// void SetCache(CacheSet *cacheSetptr, unsigned long tag, char instr)
// {
//     CacheSet cacheset = *cacheSetptr;
//     int i;
//     int found = 0;
//     int full = 1;
//     unsigned long fulltag;
//     unsigned int fullSmallest;
//     //Check if tag is in cache
//     for(i = 0; i < cacheset.E; i++)
//     {
//         if(cacheset.cacheLines[i].valid == 1)
//         {
//             if(cacheset.cacheLines[i].tag == tag)
//             {
//                 g_Hits++;
//                 if(instr == 'M')
//                 {
//                     g_Hits++;
//                 }
//                 found = 1;
//                 cacheset.cacheLines[i].used++;
//                 break;
//             }
//         }
//     }
//     //If not found
//     if(found == 0)
//     {
//         g_Miss++;
//         if(instr == 'M')
//         {
//             g_Hits ++;
//         }

//         //Check for empty lines
//         for(i = 0; i < cacheset.E; i++)
//         {
//             if(cacheset.cacheLines[i].valid == 0)
//             {
//                 cacheset.cacheLines[i].valid = 1;
//                 cacheset.cacheLines[i].used = 0;
//                 if(instr == 'M')
//                 {
//                    cacheset.cacheLines[i].used++;
//                 }
//                 cacheset.cacheLines[i].tag = tag;
//                 full = 0;
//                 break;
//             }
//         }

//         //If no empty lines
//         if(full == 1)
//         {   
//             fulltag = cacheset.cacheLines[0].tag;
//             fullSmallest = cacheset.cacheLines[0].used;
//             for(i = 0; i < cacheset.E; i++)
//             {
//                 if(cacheset.cacheLines[i].used <= fullSmallest)
//                 {
//                     fulltag = cacheset.cacheLines[i].tag;
//                 }
//             }

//             g_Evictions++;
//             cacheset.cacheLines[fulltag].valid = 1;
//             cacheset.cacheLines[fulltag].used = 0;
            
//             if(instr == 'M')
//             {
//                 cacheset.cacheLines[i].used++;
//             }
//             cacheset.cacheLines[fulltag].tag = tag;
//         }
//     }
// }
