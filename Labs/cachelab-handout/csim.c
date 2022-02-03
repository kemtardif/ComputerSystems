#include "cachelab.h"
#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <string.h>

void parseCLArgs(long * sp, long * Ep, long * bp, FILE * fp, int argc, char *argv[]);

int main(int argc, char *argv[])
{
    //Define our cache
    long s; 
    long E;
    long b; 
    FILE *f = NULL;

    //First parse the command-line arguments
    parseCLArgs(&s, &E, &b, f, argc, argv);


    //printSummary(0, 0, 0);
    return 0;
}

void parseCLArgs(long *sp, long *Ep, long *bp, FILE *fp, int argc, char *argv[])
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
            fp = fopen(optarg, "r");  
            if(fp == NULL)
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
