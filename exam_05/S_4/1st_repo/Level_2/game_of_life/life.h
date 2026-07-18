#ifndef LIFE_H
#define LIFE_H

#include <stdlib.h>
#include <unistd.h>

int putchar(int c);
char **create_board(int w, int h);
void free_board(char **b, int h);
void game_of_life(int w, int h, int it);

#endif
