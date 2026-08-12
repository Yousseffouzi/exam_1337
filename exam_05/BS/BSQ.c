#include "BSQ.h"

ga g;

int check_line(char *line, int len)
{
    if(len <= 0)
        return 1;
    if(line[len -1] == '\n')
        line[--len] = '\0';
    if(g.w == -1)
        g.w = len;
    if(g.w != len)
        return 1;
    for (int i = 0; i < len; i++)
        if(line[i] != g.empty && line[i] != g.obsta)
            return 1;
    return 0;
}

void f_map()
{
    if(g.cells)
        for(int y = 0; y < g.h; y++)
            free(g.cells[y]);
    free(g.cells);
    g.cells = NULL;
}

int read_map(FILE *f)
{
    if (fscanf(f, "%d %c %c %c \n", &g.h, &g.empty, &g.obsta, &g.draw) != 4 || 
        g.h <= 0 ||
        g.empty == g.obsta || g.obsta == g.draw || g.empty == g.draw)
        return 1;
    g.cells = calloc(g.h , sizeof (char *));
    if(!g.cells)
        return 1;
    g.w = -1;
    for (int y = 0; y < g.h; y++)
    {
        char *line = NULL;
        size_t size = 0;
        int len = getline(&line, &size, f);
        if (check_line(line, len))
        {
            free(line);
            f_map();
            return 1;
        }
        g.cells[y] = line;
    }
    return 0;
}

int square_ok(int x, int y, int size)
{
    for (int j = y; j < y + size; j++)
        for (int i = x; i < x + size; i++)
            if(g.cells[j][i] == g.obsta)
                return 0;
    return 1;
}

void find_bsq()
{
    for (int y = 0; y < g.h; y++){
        for (int x = 0; x < g.w; x++){
            int size = 0;
            while (y + size < g.h && x + size < g.w && square_ok(x, y, size + 1))
                size++;
            if(size > g.square_size)
            {
                g.square_size = size;
                g.start.x = x;
                g.start.y = y;
            }
        }
    }
}

void draw_print()
{
    for (int j = g.start.y; j < g.start.y + g.square_size; j++)
        for (int i = g.start.x; i < g.start.x + g.square_size; i++)
            g.cells[j][i] = g.draw;
    for (int j = 0; j < g.h; j++)
        fprintf(stdout, "%s\n", g.cells[j]);
}

void    run(FILE *f)
{
    g = (ga){0};
    g.w = -1;
    if(!f || read_map(f))
    {
        fprintf(stderr, "map error\n");
        return ;
    }
    find_bsq();
    draw_print();
    f_map();
}


//int main check ac either stdin or a file 
int main(int ac, char **av)
{
    if (ac == 1)
        run(stdin);
    else
    for (int i = 1; i < ac ; i++)
    {
        FILE *f = fopen(av[i], "r");
        run(f);
        if(f)
            fclose(f);
    }
    return 0;
}