#include "cachelab.h"
#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <string.h>

struct cacheLine 
{
    unsigned int valid;
    unsigned long tag;
};


void parseArgs(long * sp, long * Ep, long * bp, FILE ** fp, int argc, char *argv[]);
void InitCache(struct cacheLine **cache, long S, long E);
void freeMemory(struct cacheLine **cache, long S);

int main(int argc, char *argv[])
{
    //Cache parameters
    struct cacheLine **cache;
    long s;
    long S;
    //long t; 
    long E;
    long b;

    //File reading parameters
    FILE *f = NULL;
    char fline[1000];
    // size_t flen = 0;
    // size_t fread;

    //First parse the command-line arguments
    parseArgs(&s, &E, &b, &f, argc, argv);
    S = 1 << s;
    //t = (1 << 6) - s - b;

    //Initialize cache with given values
    cache = malloc(S * sizeof(struct cacheLine *));
    if(cache)
    {
        InitCache(cache, S, E);
    }
    else 
    {
        fprintf(stderr, "Error while creating the cache.");
        exit(EXIT_FAILURE);
    }

    //Read file
    while (fgets(fline,100, f)) {
        //Check the instruction
        //Read or write to te cache
        //update counter
    }

    //printSummary(0, 0, 0);
    fclose(f);
    freeMemory(cache, S);
    return 0;
}

void parseArgs(long *sp, long *Ep, long *bp, FILE **fp, int argc, char *argv[])
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
            if(!*fp)
            {
                fprintf(stderr, "%s : Not a valid file path\n",optarg);
                exit(EXIT_FAILURE);
            }
            break;
            default:
            fprintf(stderr, "Usage: %s [-sEbt] \n", argv[0]);
            exit(EXIT_FAILURE);
        }
    }
}
void InitCache(struct cacheLine **cache, long S, long E)
{
    long i;
    long y;
    
    for(i = 0; i < S; i++)
    {      
        *(cache + i) = malloc(E * sizeof(struct cacheLine));
        if(*(cache + i))
        {
            for(y = 0; y < E; y++)
            {
                ((*(cache + i)) + y)->valid = 0;
            }
        }
        else
        {
            fprintf(stderr, "Error while creating the cache.");
            exit(EXIT_FAILURE);
        }
    }
}

void freeMemory(struct cacheLine **cache, long S)
{
    int i;
    for(i = 0; i < S; i++)
    {      
        free(*(cache + i));
    }
    free(cache);
}
