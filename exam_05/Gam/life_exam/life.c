#include "life.h"

void allocate_grid(t_life *life)
{
    int i;

    life->grid = (int **)malloc(life->height * sizeof(int *));
    life->new_grid = (int **)malloc(life->height * sizeof(int *));
    if (!life->grid || !life->new_grid)
        return;
    for (i = 0; i < life->height; i++)
    {
        life->grid[i] = (int *)calloc(life->width, sizeof(int));
        life->new_grid[i] = (int *)calloc(life->width, sizeof(int));
    }
}

void free_grid(t_life *life)
{
    int i;

    for (i = 0; i < life->height; i++)
    {
        free(life->grid[i]);
        free(life->new_grid[i]);
    }
    free(life->grid);
    free(life->new_grid);
}

t_life *ft_create(int w, int h, int iter)
{
    t_life *life = malloc(sizeof(t_life));
    if (!life)
        return (NULL);
    life->width = w;
    life->height = h;
    life->iterations = iter;
    life->pen_x = 0;
    life->pen_y = 0;
    life->pen_down = 0;
    allocate_grid(life);
    return (life);
}

void ft_destroy(t_life *life)
{
    free_grid(life);
    free(life);
}

void ft_read_commands(t_life *life)
{
    char c;

    while (read(0, &c, 1) > 0)
    {
        if (c == 'x')
            life->pen_down = !life->pen_down;
        else if (c == 'w' && life->pen_y > 0)
            life->pen_y--;
        else if (c == 'a' && life->pen_x > 0)
            life->pen_x--;
        else if (c == 's' && life->pen_y < life->height - 1)
            life->pen_y++;
        else if (c == 'd' && life->pen_x < life->width - 1)
            life->pen_x++;

        if (life->pen_down)
            life->grid[life->pen_y][life->pen_x] = 1;
    }
}

int count_neighbors(t_life *life, int y, int x)
{
    int count = 0;
    for (int dy = -1; dy <= 1; dy++)
    {
        for (int dx = -1; dx <= 1; dx++)
        {
            if (dy == 0 && dx == 0)
                continue;
            int ny = y + dy;
            int nx = x + dx;
            if (ny >= 0 && ny < life->height && nx >= 0 && nx < life->width)
                count += life->grid[ny][nx];
        }
    }
    return (count);
}

void ft_simulate(t_life *life)
{
    for (int iter = 0; iter < life->iterations; iter++)
    {
        for (int y = 0; y < life->height; y++)
        {
            for (int x = 0; x < life->width; x++)
            {
                int neighbors = count_neighbors(life, y, x);
                if (life->grid[y][x])
                {
                    if (neighbors < 2 || neighbors > 3)
                        life->new_grid[y][x] = 0;
                    else
                        life->new_grid[y][x] = 1;
                }
                else
                {
                    if (neighbors == 3)
                        life->new_grid[y][x] = 1;
                    else
                        life->new_grid[y][x] = 0;
                }
            }
        }
        for (int y = 0; y < life->height; y++)
            for (int x = 0; x < life->width; x++)
                life->grid[y][x] = life->new_grid[y][x];
    }
}

void ft_print_grid(t_life *life)
{
    for (int y = 0; y < life->height; y++)
    {
        for (int x = 0; x < life->width; x++)
            putchar(life->grid[y][x] ? 'O' : ' ');
        putchar('\n');
    }
}

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