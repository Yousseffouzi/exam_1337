#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

typedef struct pen
{
    int x;
    int y;
    int is_down;
}pen;

char **creat_b(int w, int h)
{
    char **board = malloc(sizeof (char *) * h);
    if(!board)
        return NULL;
    for (int j = 0; j < h; j++)
    {
        board[j] = malloc(w);
        if(!board[j])
        {
            while(j--)
                free(board[j]);
            free(board);
            return NULL;
        }
        for (int i = 0; i < w; i++)
            board[j][i] = ' ';
    }
    return board;
}

void f_board(char **board, int h)
{
    for (int j = 0; j < h; j++)
        free(board[j]);
    free(board);
}

int count(char **board, int w, int h, int x, int y)
{
    int n = 0;
    for (int j = -1; j < 2; j++){
        for (int i = -1; i < 2; i++){
            if((i || j) &&
                (j + y > -1 && j + y < h) &&
                (i + x > -1 && i + x < w) &&
                board[j + y][i + x] == 'O')
                n++;
        }
    }
    return n;
}

void iter(char **board, int w, int h)
{
    char **tmp = creat_b(w, h);
    if(!tmp)
        return;
    for (int j = 0; j < h; j++){
        for (int i = 0; i < w; i++){
            int n = count(board, w, h, i, j);
            if(board[j][i] == 'O' && ((n == 2) || n == 3) || 
                (board[j][i] == ' ' && (n == 3)))
                tmp[j][i] = 'O';
            else
                tmp[j][i] = ' ';
        }
    }
    for (int j = 0; j < h; j++){
        for (int i = 0; i < w; i++){
           board[j][i] = tmp[j][i]; 
        }
    }
    f_board(tmp , h);
}

void p_board(char **board, int w, int h)
{
    for (int j = 0; j < h; j++){
        for (int i = 0; i < w; i++){
            putchar(board[j][i]);
        }
        putchar('\n');
    }
}

int main(int ac, char **av)
{
    if(ac != 4)
        return 1;
    int w = atoi(av[1]);
    int h = atoi(av[2]);
    int i = atoi(av[3]);

    char **board = creat_b(w, h);
    if(!board)
        return 1;
    char c;
    pen p = {0, 0, 0};
    while (read(0, &c, 1) > 0)
    {
        if(c == 'x')
            p.is_down = !p.is_down;
        else if (c == 'w' && p.y > 0)
            p.y--;
        else if (c == 's' && p.y <  h - 1)
            p.y++;
        else if (c == 'a' && p.x > 0)
            p.x--;
        else if (c == 'd' && p.x <  w - 1)
            p.x++;
        if(p.is_down)
            board[p.y][p.x] = 'O';
    }
    while (i--)
        iter(board, w, h);
    p_board(board, w, h);
    f_board(board, h);
}