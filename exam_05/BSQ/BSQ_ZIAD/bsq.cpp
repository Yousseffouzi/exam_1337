#include "bsq.h"

int slen(char *s)
{
    int i = 0;
    for ( ; s[i]; i++)
    {}
    return i;
}

int min(int a, int b, int c)
{
    return a < b ? (a < c ? a : c) : (b < c ? b : c);
}

int bsq(FILE *file)
{
    int hight = 0;
    char empty = 0, obstacle = 0, full = 0;
    if (fscanf(file, "%d%c%c%c\n", &hight, &empty, &obstacle, &full) != 4)
        return 1;
    if (hight <= 0 || empty == obstacle || empty == full || obstacle == full)
        return 1;
    char **map = calloc(hight, sizeof(char *));
    int i = 0, w;
    char *line = NULL;
    size_t len = 0;

    for (; getline(&line, &len, file) != -1; i++)
    {
        if (i == hight)
            return 1;
        map[i] = line;
        line = NULL;
        len = 0;
        if (i == 0)
        {
            w = slen(map[0]);
            if (w < 2 || map[0][w-1] != '\n')
                return 1;
        }
        else if (w != slen(map[i]) || map[i][w-1] != '\n')
            return 1;
    }
    if (i < hight)
        return 1;

    int **dp = calloc(hight + 1, sizeof(int*));
    for (int i = 0; i <= hight; i++)
        dp[i] = calloc(w + 1, sizeof(int));
    int y = 0, x = 0, size = 0;

    for (int i = 0; i < hight; i++)
    {
        for (int j = 0; j < w - 1; j++)
        {
            if (map[i][j] == empty)
            {
                dp[i+1][j+1] = 1 + min(dp[i][j], dp[i+1][j], dp[i][j+1]);
                if (size < dp[i+1][j+1])
                    y = i, x = j, size = dp[i+1][j+1];
            }
            else if (map[i][j] != obstacle)
                return 1;
        }
    }
    
    for (int i = y - size + 1; i <= y; i++)
    {
        for (int j = x - size + 1; j <= x; j++)
            map[i][j] = full;
    }
    for (int i = 0; i < hight; i++)
        fprintf(stdout, "%s", map[i]);
    return 0;
}   

int main(int ac, char **av){
    if (ac == 1)
    {
        if (bsq(stdin))
            fprintf(stderr, "bad map\n");
    }
    else
    {
        for (int a = 1; a < ac; a++)
        {
            FILE *file = fopen(av[a], "r");

            if (!file || bsq(file))
                fprintf(stderr, "bad map\n");

            if (file)
                fclose(file);
        }
    }

    return 0;
}