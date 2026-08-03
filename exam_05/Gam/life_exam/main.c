#include "life.h"

int main(int ac, char **av)
{
    if (ac != 4)
        return (1);

    int w = atoi(av[1]);
    int h = atoi(av[2]);
    int iter = atoi(av[3]);

    t_life *game = ft_create(w, h, iter);
    if (!game)
        return (1);

    ft_read_commands(game);
    ft_simulate(game);
    ft_print_grid(game);

    ft_destroy(game);
    return (0);
}
