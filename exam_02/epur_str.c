#include <unistd.h>

int is_space(char c)
{
    if(c <= 32)
        return (1);
    return (0);
}


int main(int ac, char **av)
{
    int i;
    int space;

    if (ac == 2)
    {
        i = 0;
        space = 0;
        while (is_space(av[1][i]))
            i++;
        while (av[1][i])
        {
            if (is_space(av[1][i]))
                space = 1;
            if (!is_space(av[1][i]))
            {
                if(space)
                    write(1, "   ", 3);
                space = 0;
                write(1, &av[1][i], 1);
            }
            i++;
        }
    }
    write(1, "\n", 1);
}