#include "life.h"

void init_border(int width, int height, int iterations, t_game *border)
{
    border->width = width;
    border->height = height;
    border->iterations = iterations;
    border->cells = calloc(2, sizeof(char **));
    border->cells[0] = calloc(height, sizeof(char *));
    border->cells[1] = calloc(height, sizeof(char *));
    for (int i = 0; i < height; i++)
    {
        border->cells[0][i] = calloc(width, sizeof(char));
        border->cells[1][i] = calloc(width, sizeof(char));
        for (int j = 0; j < width; j++)
        {
            border->cells[0][i][j] = DEAD;
        }
    }
}

void create_cells(t_game *border)
{
    char ch, should_draw = 0;
    int x = 0, y = 0;
    while(read(0, &ch, 1) > 0)
    {
        switch(ch)
        {
            case 'a': x--; break;
            case 'd': x++; break;
            case 'w': y--; break;
            case 's': y++; break;
            case 'x': should_draw = !should_draw; break;
            default: return;
        }
        if (should_draw)
        {
            if (x >= 0 && x < border->width && 
                y >= 0 && y < border->height)
            {
                border->cells[0][y][x] = 'O';
            }
        }
    }
}

void print_border(t_game *border)
{
    char print_dot;
    for (int i = 0; i < border->height; i++)
    {
        print_dot = 0;
        for (int j = 0; j < border->width; j++)
        {
            if (border->cells[0][i][j] == ALIVE)
                print_dot = 1;
            if (!print_dot && border->cells[0][i][j] == DEAD)
                continue;
            if (print_dot && border->cells[0][i][j] == DEAD)
                print_dot = 0;
            putchar(border->cells[0][i][j]);
        }
        putchar('\n');
    }
}

int count_neighbors(t_game *border, int x, int y)
{
    int row = y - 1;
    int col = x - 1;
    int count = 0;
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (i == 1 && j == 1)
                continue;
            if (row + i >= 0 && row + i < border->height &&
                col + j >= 0 && col + j < border->width &&
                border->cells[0][row + i][col + j] == 'O')
            {
                count++;
            }
        }
    }
    return count;
}

void copy_cells(t_game *border)
{
    for (int y = 0; y < border->height; y++)
    {
        for (int x = 0; x < border->width; x++)
        {
            border->cells[0][y][x] = border->cells[1][y][x];
        }
    }
}

void update_border(t_game *border)
{
    for (int y = 0; y < border->height; y++)
    {
        for (int x = 0; x < border->width; x++)
        {
            int neighbors = count_neighbors(border, x, y);
            if (border->cells[0][y][x] == ALIVE)
            {
                if (neighbors < 2 || neighbors > 3)
                    border->cells[1][y][x] = DEAD;
                else
                    border->cells[1][y][x] = ALIVE;
            }
            else
            {
                if (neighbors == 3)
                    border->cells[1][y][x] = ALIVE;
                else
                    border->cells[1][y][x] = DEAD;
            }
        }
    }
    copy_cells(border);
}

void cleanup(t_game *border)
{
    for (int i = 0; i < border->height; i++)
    {
        free(border->cells[0][i]);
        free(border->cells[1][i]);
    }
    free(border->cells[0]);
    free(border->cells[1]);
    free(border->cells);
}

int main(int argc, char *argv[])
{
    (void)argc;
    if (argc != 4)
        return 1;
    t_game border;
    init_border(atoi(argv[1]), atoi(argv[2]), atoi(argv[3]), &border);
    create_cells(&border);
    for (int i = 0; i < border.iterations; i++)
    {
        update_border(&border);
    }
    print_border(&border);
    cleanup(&border);
}
