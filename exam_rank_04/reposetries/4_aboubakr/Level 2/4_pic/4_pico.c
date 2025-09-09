#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>


int    picoshell(char **cmds[])
{
	int res = 0;
	int pid;
	int fds[2];
	int prev_fd = -1;
	int i = 0;
	int status;

	while (cmds[i])
	{
		if (cmds[i + 1])
			pipe(fds);
		
		pid = fork();
		if (pid == -1)
			return 1;
		
		if (!pid)
		{
			if (prev_fd != -1)
			{
				dup2(prev_fd, 0);
				close (prev_fd);
			}

			if (cmds[i + 1])
			{
				dup2(fds[1], 1);
				close (fds[1]);
			}

			execvp(cmds[i][0], cmds[i]);
			return 1;
		}

		if (prev_fd != -1)
			close (prev_fd);

		if (cmds[i + 1])
		{
			close (fds[1]); // khdemna bih f child khasso itsed
			prev_fd = fds[0];
		}

		while (wait(&status) == -1)
		{
			if (WIFEXITED(status) && !WEXITSTATUS(status))
				res = 1;
		}

		i++;
	}
	return res;
}

int main(void)
{
    char *cmd1[] = {"ls", "-l", NULL};
    char *cmd2[] = {"grep", ".c", NULL};
    char *cmd3[] = {"wc", "-l", NULL};

    char **cmds[] = {cmd1, cmd2, cmd3, NULL};

    picoshell(cmds);
    return 0;
}
