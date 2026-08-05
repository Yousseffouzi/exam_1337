 #include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

typedef struct pen
{
    int x;
    int y;
    int is_down;
} pen;

void print_board(char **board, int w, int h)
{
    for (int y = 0; y < h; y++)
    {
        for (int x = 0; x < w; x++)
            putchar(board[y][x]);
        putchar('\n');
    }
}

char **create_board(int w, int h)
{
    char **board = malloc(sizeof(char *) * h);
    if (!board)
        return NULL;

    for (int y = 0; y < h; y++)
    {
        board[y] = malloc(w);
        if (!board[y])
        {
            while (y--)
                free(board[y]);
            free(board);
            return NULL;
        }

        for (int x = 0; x < w; x++)
            board[y][x] = ' ';
    }
    return board;
}

void free_board(char **board, int h)
{
    for (int y = 0; y < h; y++)
        free(board[y]);
    free(board);
}

int count(char **board, int w, int h, int x, int y)
{
    int n = 0;

    for (int dy = -1; dy <= 1; dy++)
        for (int dx = -1; dx <= 1; dx++)
            if ((dx || dy) &&
                x + dx >= 0 && x + dx < w &&
                y + dy >= 0 && y + dy < h &&
                board[y + dy][x + dx] == 'O')
                n++;

    return n;
}

void iter_game(char **board, int w, int h)
{
    char **tmp = create_board(w, h);
    if (!tmp)
        return;

    for (int y = 0; y < h; y++)
        for (int x = 0; x < w; x++)
        {
            int n = count(board, w, h, x, y);

            if ((board[y][x] == 'O' && (n == 2 || n == 3)) ||
                (board[y][x] == ' ' && n == 3))
                tmp[y][x] = 'O';
            else
                tmp[y][x] = ' ';
        }

    for (int y = 0; y < h; y++)
        for (int x = 0; x < w; x++)
            board[y][x] = tmp[y][x];

    free_board(tmp, h);
}

int main(int ac, char **av)
{
    if (ac != 4)
        return 1;

    int w = atoi(av[1]);
    int h = atoi(av[2]);
    int iter = atoi(av[3]);

    char **board = create_board(w, h);
    if (!board)
        return 1;

    pen p = {0, 0, 0};
    char c;

    while (read(0, &c, 1) > 0)
    {
        if (c == 'x')
            p.is_down = !p.is_down;
        else if (c == 'w' && p.y > 0)
            p.y--;
        else if (c == 's' && p.y < h - 1)
            p.y++;
        else if (c == 'a' && p.x > 0)
            p.x--;
        else if (c == 'd' && p.x < w - 1)
            p.x++;

        if (p.is_down)
            board[p.y][p.x] = 'O';
    }

    while (iter--)
        iter_game(board, w, h);

    print_board(board, w, h);
    free_board(board, h);
}