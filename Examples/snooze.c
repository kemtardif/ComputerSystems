#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

void signalHandler(int n)
{
    return;
}

int main(int argc, char *argv[])
{
    char * arg1 = argv[1];
    int time;
    sigset_t mask, oldMask;

    if(arg1 == NULL)
    {
        printf("Must have at least one argument");
        exit(0);
    }

    time = atoi(arg1);

    if(time == 0 )
    {
         printf("Must enter valid time argument");
        exit(0);
    }


    if(signal(SIGINT, signalHandler) == SIG_ERR)
    {
        printf("Signal error");
        exit(0);
    }

    sigemptyset(&mask);
    sigaddset(&mask, SIGINT);

    sigprocmask(SIG_BLOCK, &mask, &oldMask);
    sleep(5);


    sigprocmask(SIG_SETMASK, &oldMask, NULL);
    printf("Slept for 5 seconds and you can't do shit about it \n");

    unsigned int timeLL = sleep(time);

    printf("There is %i of %i seconds left. Good job, you cancelled my sleep.", timeLL, time);
    return 0;
}