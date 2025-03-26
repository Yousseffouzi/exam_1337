#include <stdlib.h>
#include <unistd.h>

char **ft_split(char *str)
{
    int i;
    int j;
    int k;
    char **split;

    i = 0;
    k = 0;
    if (!(split = (char **)malloc(sizeof(char *) * 256)))
        return (NULL);
    while(str[i] == ' ' || str[i] == '\t' || str[i] == '\n')
        i++;
    while(str[i])
    {
        j = 0;
        if(!(split[k] = (char *)malloc(sizeof(char) * 4096)))
            return (NULL);
        while(str[i] != ' ' && str[i] != '\t' && str[i] != '\n' && str[i])
            split[k][j++] = str[i++];
        while(str[i] == ' ' || str[i] == '\t' || str[i] == '\n')
            i++;
        split[k][j] = '\0';
        k++;
    }
    split[k] = NULL;
    return (split);
}

int main(int ac, char **av)
{
    int i;
    int j;
    char **split;

    if (ac == 2)
    {
        i = 0;
        split = ft_split(av[1]);
        while(split[i])
            i++;
        i--;
        while(i >= 0)
        {
            j = 0;
            while(split[i][j])
            {
                write(1, &split[i][j], 1);
                j++;
            }
            if (i > 0)
                write(1, " ", 1);
            i--;
        }
    }
    write(1, "\n", 1);
    return (0);
}