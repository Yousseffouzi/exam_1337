#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int ft_popen(const char *file, char *const argv[], char type)
{
    int fd[2];
    pid_t pid;

    if (!file || !argv || (type != 'r' && type != 'w'))
        return -1;
    
    if (pipe(fd) == -1)
        return -1;

    pid = fork();
    if (pid == -1)
    {
        close(fd[0]);
        close(fd[1]);
        return -1;
    }
    if (pid == 0)
    {
        if (type == 'r')
        {
            close(fd[0]);
            dup2(fd[1], STDOUT_FILENO);
            close(fd[1]);
        }
        else
        {
            close(fd[1]);
            dup2(fd[0], STDIN_FILENO);
            close(fd[0]);
        }
        execvp(file, argv);
        exit(1);
    }
    else
    {
        if (type == 'r')
        {
            close(fd[1]);
            return (fd[0]);
        }
        else
        {
            close(fd[0]);
            return (fd[1]);
        }
    }
}


#include <stdio.h>
int main(void)
{
    int fd;

    fd = ft_popen("wc", (char *const []){"wc", "-l", NULL}, 'w');
    if (fd == -1)
        return 1;
    write(fd, "line 1\n", 7);
    write(fd, "line 2\n", 7);
    write(fd, "line 3\n", 7);
    close(fd); // Closes pipe to trigger wc output
    return 0;
}

// int main(void)
// {
//     char buffer[128];
//     ssize_t bytes;
//     int fd = ft_popen("ls", (char *const []){"ls", NULL}, 'r');
//     if (fd == -1)
//     {
//         perror("ft_popen failed");
//         return (1);
//     }

//     while ((bytes = read(fd, buffer, sizeof(buffer))) > 0)
//         write(STDOUT_FILENO, buffer, bytes);

//     close(fd);
//     return (0);
// }
