#pragma once

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct point
{
    int x;
    int y;
}p;

typedef struct game
{
    int w;
    int h;
    char empty;
    char obsta;
    char draw;

    char **cells;
    p start;
    int square_size;

}ga;