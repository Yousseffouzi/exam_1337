#ifndef LIFE_H
#define LIFE_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>

#define DEAD ' '
#define ALIVE 'O'

typedef struct s_game
{
    int width;
    int height;
    int iterations;
    char ***cells;
}  t_game;

void init_border(int width, int height, int iterations, t_game *border);

void print_border(t_game *border);

#endif