#include "life.h"

char **create_board(int w, int h) {
    char **b = calloc(h, sizeof(char*));
    if (!b) return NULL;
    for (int i = 0; i < h; i++) {
        if (!(b[i] = calloc(w, 1))) {
            while (i--) free(b[i]);
            free(b);
            return NULL;
        }
        for (int j = 0; j < w; j++) b[i][j] = ' ';
    }
    return b;
}

void free_board(char **b, int h) {
    if (!b) return;
    for (int i = 0; i < h; i++) free(b[i]);
    free(b);
}

int count_neighbors(char **b, int x, int y, int w, int h) {
    int c = 0;
    for (int dy = -1; dy <= 1; dy++)
        for (int dx = -1; dx <= 1; dx++)
            if ((dx || dy) && x + dx >= 0 && x + dx < w && y + dy >= 0 && y + dy < h)
                c += (b[y + dy][x + dx] == '0');
    return c;
}

void game_of_life(int w, int h, int it) {
    char **b = create_board(w, h);
    if (!b) return;

    char buf;
    int x = 0, y = 0, d = 0;
    while (read(0, &buf, 1) > 0) {
        if (buf == 'x') d = !d;
        else if (buf == 'w' && y > 0) y--;
        else if (buf == 'a' && x > 0) x--;
        else if (buf == 's' && y < h - 1) y++;
        else if (buf == 'd' && x < w - 1) x++;
        if (d) b[y][x] = '0';
    }

    while (it--) {
        char **nb = create_board(w, h);
        if (!nb) { free_board(b, h); return; }
        for (int i = 0; i < h; i++) {
            for (int j = 0; j < w; j++) {
                int n = count_neighbors(b, j, i, w, h);
                if ((b[i][j] == '0' && (n == 2 || n == 3)) || (b[i][j] == ' ' && n == 3))
                    nb[i][j] = '0';
            }
        }
        free_board(b, h);
        b = nb;
    }

    for (int i = 0; i < h; i++) {
        for (int j = 0; j < w; j++) putchar(b[i][j]);
        putchar('\n');
    }
    free_board(b, h);
}
