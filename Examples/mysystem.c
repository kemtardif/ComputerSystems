#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

extern char **environ;

int mysystem(char *command)
{

    if(command == NULL)
    {
        fprintf(stderr, "Command is NULL");
        return -1;
    }
    pid_t pid;
    int execerr, status;
    char * args[] = {
        "/bin/sh", 
        "-c", 
        command, 
        NULL
    };

    pid = fork();

    if(pid < 0)
    {
        fprintf(stderr, "pid error");
        return -1;
    }
    if(pid == 0) //Child process
    {
        execerr = execve(args[0], args, environ);

        if(execerr < 0)
        {
            fprintf(stderr, "execve error (in child)");
            exit(-1);
        }
    } 

    if(waitpid(-1, &status, 0) > 0)
    {
        if(status < 0)
        {
            fprintf(stderr, "execve error (parent)");
                return -1;
        }

        if(WIFEXITED(status))
            return WEXITSTATUS(status);

        if(WIFSIGNALED(status))
        return WTERMSIG(status);
    }

    return -1;
}