#include "life.h"

int atoi(const char *s) {
    int n = 0, sign = 1;
    while (*s == ' ' || *s == '\t') s++;
    if (*s == '-') { sign = -1; s++; }
    else if (*s == '+') s++;
    while (*s >= '0' && *s <= '9') n = n * 10 + (*s++ - '0');
    return n * sign;
}

int main(int ac, char **av) {
    if (ac != 4) return 1;
    int w = atoi(av[1]), h = atoi(av[2]), it = atoi(av[3]);
    if (w <= 0 || h <= 0 || it < 0) return 1;
    game_of_life(w, h, it);
    return 0;
}
