#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


typedef struct life
{
    char *cells;
    int pendown;
    int px;
    int py;
    int w;
    int h;
    int iters;

} t_life;


int init(t_life* l, int ac, char **av)
{
    l->cells = NULL;
    l->pendown = 0;
    l->px = 0;
    l->py = 0;
    l->w = atoi(av[1]);
    l->h = atoi(av[2]);
    l->iters = atoi(av[3]);
    if (l->w <= 0 || l->h <= 0 || l->iters < 0)
        return 0;
    l->cells = (char*)calloc(l->w * l->h, 1);
    if (!l->cells)
        return 0;
    return 1;
}

int draw(t_life* l)
{
    char buf[4000];
    int r = 0;
    int i;
    while ((r = read(0, buf, 4000)) > 0)
    {
        i = 0;
        while (i < r)
        {
            char c = buf[i++];
            if (c == 'x')
                l->pendown = !l->pendown;
            else if (c == 'w')
                l->py--;
            else if ( c == 's')
                l->py++;
            else if (c == 'a')
                l->px--;
            else if ( c == 'd')
                l->px++;
            else continue;
            if (l->pendown)
            {
                if (l->px >= 0 && l->px < l->w && l->py >= 0 && l->py < l->h)
                    l->cells[l->py * l->w + l->px] = 1;
            }
        }
    }
    if (r < 0)
        return 0;
    return 1;
}

void print(t_life* l)
{
    for (int i = 0; i < l->h; i++)
    {
        for (int j = 0 ;j < l->w; j++)
        {
            if (l->cells[i * l->w + j])
                putchar('O');
            else
                putchar('-');
        }
        putchar('\n');
    }
}

int jiran(t_life *l, int x, int y)
{
    int alive = 0;
    int offsetx;
    int offsety;
    int newx;
    int newy;

    for (offsety = -1 ; offsety <= 1; offsety++)
    {
        for (offsetx = -1; offsetx <= 1; offsetx++)
        {
            newx = x + offsetx;
            newy = y + offsety;
            if ((offsetx || offsety)
                && newx >= 0 && newx < l->w
                && newy >= 0 && newy < l->h)
                alive += l->cells[newy * l->w + newx];
        }
    }
    return alive;
}

int step(t_life* l)
{
    int n = 0;//cells alive
    char* next = NULL;
    next = (char*)calloc(l->w*l->h, 1);
    if (!next)
        return 0;
    for (int i = 0; i < l->h; i++)
    {
        for (int j = 0; j < l->w; j++)
        {
            n = jiran(l, j, i);
            if (n==3 || (n==2 && l->cells[i*l->w+j]))
                next[i*l->w+j] = 1;
        }
    }
    free(l->cells);
    l->cells = next;
    return 1;
}

int main(int ac, char **av)
{
    t_life l;

    if (!init(&l, ac, av))
        return (free(l.cells), 1);
    if (!draw(&l))
        return (free(l.cells), 1);
    while (l.iters-- > 0)
    {
        if (!step(&l))
            return (free(l.cells), 1);
    }
    print(&l);
    free(l.cells);
    return 0;
}