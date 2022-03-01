#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>

#define LENGTH 100

int main(int argc, char **argv, char **envp)
{
    int i, status;
    pid_t pid;

   for(i = 0; i < 5; i++)
   {
       if(fork() == 0)
       {
           char *s = "sEGFAULT";
           s[0] = 'S'; // Seg Fault

           exit(0); //Never Accessed
       }
   }

   while((pid = waitpid(-1, &status, 0)) > 0)
   {
       if(WIFEXITED(status))
       {
           printf("Child %d terminated normally with status %d ",
                pid, WEXITSTATUS(status));
       } else if (WIFSIGNALED(status))
       {
           char strng[LENGTH];
           sprintf(strng, "Child %d terminated by signal %d ", pid, WTERMSIG(status));
           psignal(WTERMSIG(status), strng);
       }
   }

   if(errno != ECHILD)
   {
       printf("waitpid error");
   }

    exit(0);
}