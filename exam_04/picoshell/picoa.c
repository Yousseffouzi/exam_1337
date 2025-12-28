#include "pico.h"


int picoshella(char **cmd[])
{
    int i = 0;
    int prev = -1;
    pid_t pid;
    int fd[2];

    while (cmd[i])
    {
        if(cmd[i + 1] && pipe(fd) == -1)
            return(1);
        pid = fork();
        if(pid == -1)
            return(1);
        if(pid == 0)
        {
            if(prev != -1)
            {
                dup2(prev, 0);
                close(prev);
            }
            if(cmd[i + 1])
            {
                dup2(fd[1], 1);
                close(fd[1]);
                close(fd[0]);
            }
            execvp(cmd[i][0], cmd[i]);
            exit(1);
        }
        if(prev != -1)
            close(prev);
        if(cmd[i + 1])
        {
            close(fd[1]);
            prev = fd[0];
        }
        i++;
    }
    
    while (wait(NULL) > 0)
        ;
    return 0;
}

