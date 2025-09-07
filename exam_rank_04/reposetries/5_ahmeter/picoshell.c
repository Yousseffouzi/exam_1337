#include <stdlib.h>
#include <unistd.h>	
#include <sys/wait.h>

static int setup_pipes(int *pipe_fd, int has_next_cmd)
{
	if (has_next_cmd)
		return pipe(pipe_fd);
	pipe_fd[0] = -1;
	pipe_fd[1] = -1;
	return 0;
}

static int setup_child_io(int in_fd, int out_fd)
{
	if (in_fd != 0 && dup2(in_fd, 0) == -1) return -1;
	if (out_fd != -1 && dup2(out_fd, 1) == -1) return -1;
	return 0;
}

static int wait_for_child(void)
{
	int ret = 0;
	int status = 0;

	while (wait(&status) > 0)
	{
		if (!WIFEXITED(status) || WEXITSTATUS(status) != 0)
			ret = 1;
	}
	return ret;
}

static void cleanup_fds(int in_fd, int pipe_fd[2])
{
	if (in_fd != 0) close(in_fd);
	if (pipe_fd[1] != -1) close(pipe_fd[1]);
	if (pipe_fd[0] != -1) close(pipe_fd[0]);
}

int    picoshell(char **cmds[])
{
	int i = 0;
	int in_fd = 0;

	while (cmds[i])
	{
		int pipe_fd[2];
		int has_next_cmd = (cmds[i + 1] != NULL);
		
		if (setup_pipes(pipe_fd, has_next_cmd) == -1)
		{
			if (in_fd != 0) close(in_fd);
			return 1;
		}
		pid_t pid = fork();
		if (pid < 0)
		{
			cleanup_fds(in_fd, pipe_fd);
			return 1;
		}
		if (pid == 0)
		{
			if (setup_child_io(in_fd, pipe_fd[1]) == -1)
				exit(1);
			cleanup_fds(in_fd, pipe_fd);
			execvp(cmds[i][0], cmds[i]);
			exit(1);
		}
		if (in_fd != 0) close(in_fd);
		if (pipe_fd[1] != -1) close(pipe_fd[1]);
		in_fd = pipe_fd[0];
		i++;
	}
	return wait_for_child();
}
