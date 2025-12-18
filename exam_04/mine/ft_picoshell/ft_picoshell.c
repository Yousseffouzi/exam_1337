#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/wait.h>

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

//Main seulement pour tester!!!
int	main(int argc, char **argv)
{
	int	cmds_size = 1;
	for (int i = 0; i < argc; i++)
	{
		if (!strcmp(argv[i], "|"))
			cmds_size++;
	}
	char ***cmds = calloc(cmds_size + 1, sizeof(char **));
	if (!cmds)
	{
		dprintf(2, "Malloc error: %m\n");
		return (1);
	}
	cmds[0] = argv + 1;
	int	cmds_i = 1;
	for (int i = 0; i < argc; i++)
	{
		if (!strcmp(argv[i], "|"))
		{
			cmds[cmds_i] = argv + i + 1;
			argv[i] = NULL;
			cmds_i++;
		}
	}
	int	ret = picoshell(cmds);
	if (ret)
		perror("picoshell");
	free(cmds);
	return(ret);
}
