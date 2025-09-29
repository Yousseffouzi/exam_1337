#include "pico.h"

int picoshell1(char **cmds[])
{
	int fds[2], previous_fd = -1;

	if (!cmds || !cmds[0])
		return (1);
	int i = 0;
	while (cmds[i])
	{
		int has_next = (cmds[i + 1] != NULL);
		if (has_next && pipe(fds) == -1)
			return (1);
		int pid = fork();
		if (pid == -1)
			return (1);
		if (pid == 0)
		{
			if (previous_fd != -1)
			{
				dup2(previous_fd, STDIN_FILENO);
				close(previous_fd);
			}
			if (has_next)
			{
				close(fds[0]);
				dup2(fds[1], STDOUT_FILENO);
				close(fds[1]);
			}
			execvp(cmds[i][0], cmds[i]);
			exit(1);
		}
		else
		{
			if (previous_fd != -1)
				close(previous_fd);	
			if (has_next)
			{
				close(fds[1]);
				previous_fd = fds[0];
			}
		}
		i++;
	}
	while(wait(NULL) > 0)
		;
	return (0);
}

// int main()
// {
// 	// char *ls[] = {NULL};
// 	// char *wc[] = {NULL};
// 	// char *lsa[] = {NULL};
// 	char *fail_cmd[] = {"nonexistent_command_12345", NULL};
//     char **cmds[] = {fail_cmd, NULL};
	
// 	return (picoshell1(cmds));
// }


