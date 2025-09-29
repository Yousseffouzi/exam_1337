/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   practice.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yofouzi <yofouzi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/29 08:51:47 by yofouzi           #+#    #+#             */
/*   Updated: 2025/09/29 09:43:18 by yofouzi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

int ft_popen(const char *file, char *const argv[], char type)
{
    int pid = 0;
    int fd[2];
    
    if(!file || !argv || !argv[0] || (type != 'r' && type != 'w'))
        return (-1);
    if(pipe(fd) == -1)
        return (-1);
    pid = fork();
    if(pid == -1)
    {
        close(fd[0]);
        close(fd[1]);
        return (-1);
    }
    if(pid == 0)
    {
        if(type == 'r')
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
        exit(127);
    }
    else
    {
        if(type == 'r')
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
    return (0);
}

// int main(void)
// {
//     int fd;
//     char buffer[1024];
//     int bytes_read;

//     fd = ft_popen("wc", (char *const []){"wc", "-c", NULL}, 'w');
//     close(fd);
//     return 0;
// }

// read
// int main(void)
// {
//     int fd;
//     char buffer[1024];
//     int bytes_read;

//     fd = ft_popen("ls", (char *const []){"ls", NULL}, 'r');

//     while ((bytes_read = read(fd, buffer, sizeof(buffer))) > 0)
//     {
//         write(1, buffer, bytes_read);
//     }
//     close(fd);
//     return 0;
// }

// write
// #include <string.h>
// int main(void)
// {
//     int fd = ft_popen("wc", (char *const []){"wc", "-c", NULL}, 'w');
//     char *msg = "Hello from ft_popen with type 'w'!\n";
//     write(fd, msg, strlen(msg));
//     close(fd);
//     return 0;
// }

// int main(void)
// {
//     // Prepare command: ls -l
//     char *cmd[] = {"ls", "-l", NULL};

//     // Get read end of pipe from ft_popen
//     int fd = ft_popen("ls", cmd, 'r');
//     if (fd == -1)
//     {
//         perror("ft_popen failed");
//         return EXIT_FAILURE;
//     }

//     // Read output from the command
//     char buffer[256];
//     ssize_t bytes_read;
//     while ((bytes_read = read(fd, buffer, sizeof(buffer) - 1)) > 0)
//     {
//         buffer[bytes_read] = '\0';  // Null-terminate the string
//         printf("%s", buffer);       // Print to stdout
//     }

//     close(fd);
//     return 0;
// }

// int main(void)
// {
//     char *cmd[] = {"cat", NULL};  // 'cat' reads from stdin

//     int fd = ft_popen("cat", cmd, 'w');
//     if (fd == -1)
//     {
//         perror("ft_popen failed");
//         return EXIT_FAILURE;
//     }

//     // Send input to 'cat'
//     const char *msg = "Hello from parent to cat!\n";
//     write(fd, msg, strlen(msg));
//     close(fd);  // Important to send EOF to 'cat'

//     // The child will echo the message back to stdout (from its stdin)

//     return 0;
// }

