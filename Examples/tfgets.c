#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>
#include <setjmp.h>

jmp_buf env;

void alrm_handler(int sig)
{
    write(STDOUT_FILENO, "Time out \n", 11);
    siglongjmp(env, 1);
}

//fgets but timeout after 5 sec
char * tfgets(char * s, int size, FILE *stream)
{
    char *p;
    signal(SIGALRM, alrm_handler);

    switch(setjmp(env))
    {
        case 0:
            alarm(5);
            p = fgets(s, size, stream);
            break;
        case 1:
            p = NULL;
            break;
        default:
            printf("NON-LOCAL JUMP ERROR");
            exit(0);
            break;
    }

    return p;
}   
