#ifndef LIFE_H
#define LIFE_H

#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

typedef struct s_life
{
    int width;
    int height;
    int iterations;
    int **grid;
    int **new_grid;
    int pen_x;
    int pen_y;
    int pen_down;
}   t_life;

t_life *ft_create(int w, int h, int iter);
void    ft_destroy(t_life *life);
void    ft_read_commands(t_life *life);
void    ft_simulate(t_life *life);
void    ft_print_grid(t_life *life);

#endif
