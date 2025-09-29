#include "pico.h"

int picoshell(char **cmd[])
{
    int fds[2];
    int prev = -1;
    int has_next;
    int pid;
    int i;

    if (!cmd || !cmd[0])
        return(1);
    i = 0;
    while(cmd[i])
    {
        has_next = (cmd[i + 1] != NULL);
        if(has_next && pipe(fds) == -1)
            return (1);
        pid = fork();
        if (pid == -1)
            return (1);
        if (pid == 0)
        {
            if (prev != -1)
            {
                dup2(prev, STDIN_FILENO);
                close(prev);
            }
            if (has_next)
            {
                close(fds[0]);
                dup2(fds[1],STDOUT_FILENO);
                close(fds[1]);
            }
            execvp(cmd[i][0],cmd[i]);
            exit(127);
        }
        else
        {
            if (prev != -1)
                close(prev);
            if(has_next)
            {
                close(fds[1]);
                prev = fds[0];
            }
        }
        i++;
    }
    while(wait(NULL) > 0)
        ;
    return (0);
}
