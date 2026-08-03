#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>


typedef struct s_life
{
    char    *cells;   /* w * h bytes: 0 = dead, 1 = alive */
    int     w;        /* width  */
    int     h;        /* height */
    int     it;       /* iterations left to run */
    int     px;       /* pen column */
    int     py;       /* pen row    */
    int     down;     /* pen touching the paper? */
}   t_life;

int     life_init(t_life *l, int ac, char **av);
void    life_set(t_life *l, int x, int y);
void    life_command(t_life *l, char c);
int     life_draw(t_life *l);
int     life_step(t_life *l);
void    life_print(t_life *l);

/*
index = y*w + x         ; a grid in a flat array
calloc, not malloc      ; dead = 0 = free of charge
read old, write new     ; STEP never touches cells until the end
px/py/down outside DRAW's read loop  ; read() may split the input
*/

int life_init(t_life *l, int ac, char **av)
{
    if (ac != 4)
        return (0);
    l->w = atoi(av[1]);
    l->h = atoi(av[2]);
    l->it = atoi(av[3]);
    l->px = 0;
    l->py = 0;
    l->down = 0;
    l->cells = NULL;
    if (l->w <= 0 || l->h <= 0 || l->it < 0)
        return (0);
    l->cells = calloc(l->w * l->h, 1);
    if (!l->cells)
        return (0);
    return (1);
}

// void life_set(t_life *l, int x, int y)
// {
//     if (x >= 0 && x < l->w && y >= 0 && y < l->h)
//         l->cells[y * l->w + x] = 1;
// }

// void life_command(t_life *l, char c)
// {
//     if (c == 'x')
//         l->down = !l->down;
//     else if (c == 'w')
//         l->py--;
//     else if (c == 's')
//         l->py++;
//     else if (c == 'a')
//         l->px--;
//     else if (c == 'd')
//         l->px++;
//     else
//         return ;
//     if (l->down)
//         life_set(l, l->px, l->py);
// }

int life_draw(t_life *l)
{
    /*
    DRAW                                    ; fill the board with the pen
    loop:
        r = read(stdin, buf, 4096)      ; grab a chunk of bytes
        if r <= 0 -> stop looping
        for each byte c of the r bytes:
            if c == 'x' -> flip down    ; pen up <-> pen down
            if c == 'w' -> py - 1       ; up    (y grows downward)
            if c == 's' -> py + 1       ; down
            if c == 'a' -> px - 1       ; left
            if c == 'd' -> px + 1       ; right
            ; anything else: ignore, just fall through

            if down AND (px,py) is inside the board
                cells[py*w + px] = 1    ; leave a mark
    if r < 0 -> failure
    */
    char    buf[4096];
    int     r;
    int     i;

    while ((r = read(0, buf, sizeof(buf))) > 0)
    {
        i = 0;
        while (i < r) // life_command(l, buf[i++]);
        {   
            char c = buf[i++];
            if (c == 'x')
                l->down = !l->down;
            else if (c == 'w')
                l->py--;
            else if (c == 's')
                l->py++;
            else if (c == 'a')
                l->px--;
            else if (c == 'd')
                l->px++;
            else
                continue ;
            if (l->down) // life_set(l, l->px, l->py);
            {
                if (l->px >= 0 && l->px < l->w && l->py >= 0 && l->py < l->h)
                    l->cells[l->py * l->w + l->px] = 1;
            }
            // i++;
        }
    }
    if (r < 0)
        return (0);
    return (1);
}

static int  neighbors(t_life *l, int x, int y)
{
    int alive;        /* running count */
    int newx;         /* neighbour's column = x + offsetx */
    int newy;         /* neighbour's row    = y + offsety */
    int offsetx;      /* column offset: -1, 0, +1 */
    int offsety;      /* row offset:    -1, 0, +1 */

    alive = 0;
    for (offsety = -1; offsety <= 1; offsety++)
    {
        for (offsetx = -1; offsetx <= 1; offsetx++)
        {
            newx = x + offsetx;
            newy = y + offsety;
            if ((offsetx || offsety)                    /* not me */
                && newx >= 0 && newx < l->w
                && newy >= 0 && newy < l->h)            /* on the board */
                alive += l->cells[newy * l->w + newx];
        }
    }
    return (alive);
}

static int neighbors(t_life *l, int x, int y)
{
    /*
    NEIGHBORS(x, y) -> count               ; how many of the 8 around me are alive
    n = 0
    for dy = -1 to +1
        for dx = -1 to +1
            skip if dx == 0 and dy == 0        ; that's me, not a neighbor
            skip if (x+dx, y+dy) is off the board  ; outside = dead = 0
            n = n + cells[(y+dy)*w + (x+dx)]   ; cell IS 0 or 1, just add it
    return n
    */
    int n;
    int dx;
    int dy;
    int nx;
    int ny;

    n = 0;
    dy = -1;
    while (dy <= 1)
    {
        dx = -1;
        while (dx <= 1)
        {
            nx = x + dx;
            ny = y + dy;
            if ((dx || dy) && nx >= 0 && nx < l->w && ny >= 0 && ny < l->h)
                n += l->cells[ny * l->w + nx];
            dx++;
        }
        dy++;
    }
    return (n);
}

int life_step(t_life *l)
{
    /*
    STEP                                    ; one generation
    allocate next = w*h bytes, zeroed   ; blank board, all dead
    if allocation failed -> failure

    for y = 0 to h-1
        for x = 0 to w-1
            n = NEIGHBORS(x, y)         ; ALWAYS counted from the OLD board
            if n == 3                   -> next[y*w+x] = 1   ; born or survives
            if n == 2 and cells[y*w+x]  -> next[y*w+x] = 1   ; survives
            ; else leave 0 — calloc already did it

    free cells                          ; old generation is finished
    cells = next                        ; struct now owns the new one
    */
    char    *next;
    int     x;
    int     y;
    int     n;

    next = calloc(l->w * l->h, 1);
    if (!next)
        return (0);
    y = 0;
    while (y < l->h)
    {
        x = 0;
        while (x < l->w)
        {
            n = neighbors(l, x, y);
            if (n == 3 || (n == 2 && l->cells[y * l->w + x]))
                next[y * l->w + x] = 1;
            x++;
        }
        y++;
    }
    free(l->cells);
    l->cells = next;
    return (1);
}



void life_print(t_life *l)
{
    /*
    PRINT
    for y = 0 to h-1
        for x = 0 to w-1
            putchar(cells[y*w + x] ? 'O' : ' ')
        putchar('\n')                   ; one newline PER ROW, not per cell
    */
    int x;
    int y;

    y = 0;
    while (y < l->h)
    {
        x = 0;
        while (x < l->w)
        {
            if (l->cells[y * l->w + x])
                putchar('O');
            else
                putchar(' ');
            x++;
        }
        putchar('\n');
        y++;
    }
}



    /*
    MAIN
        if argc != 4                        -> exit 1
        w  = atoi(argv[1])                  ; board width
        h  = atoi(argv[2])                  ; board height
        it = atoi(argv[3])                  ; iterations
        px = 0 ; py = 0 ; down = 0          ; pen: top-left, in the air
        if w <= 0 or h <= 0 or it < 0       -> exit 1
        allocate cells = w*h bytes, zeroed  ; calloc: every cell dead
        if allocation failed                -> exit 1

        call DRAW                           ; STAGE 1: stdin -> cells
        repeat it times: call STEP          ; STAGE 2: cells -> cells
        call PRINT                          ; STAGE 3: cells -> stdout
        free cells
        exit 0
    */
int main(int ac, char **av)
{
    t_life l;

    //init, check ac, check av value if valid
    if (!life_init(&l, ac, av))
    {
        if (l.cells)
            free(l.cells);
        return 1;
    }
    //allocate map, 
    if (!life_draw(&l))
        return (free(l.cells), 1);
    while (l.it-- > 0)
    {
        if (!life_step(&l))
            return (free(l.cells), 1);
    }
    life_print(&l);
    free(l.cells);
    return (0);
}


/* ============================================================
   LIFE — CHECKLIST (write in this order, compile after each)

   0. ALLOWED: atoi read putchar malloc calloc realloc free
      argc must be 4 -> ./life width height iterations
      Stages: draw -> step -> print
   1. SKELETON  : struct + empty main -> compile CLEAN now
   2. INIT      : cells=NULL FIRST / ac!=4 / atoi x3 / w,h<=0||it<0
                  / calloc(w*h,1) / check it
   3. DRAW      : state OUTSIDE read loop / c = buf[i++] /
                  junk byte -> continue / paint AFTER the chain /
                  no clamping, just don't write
      TEST       echo 'dxss' | ./a.out 3 3 0 | cat -e
   4. PRINT     : '\n' outside inner loop / exactly w chars/line
   5. NEIGHBORS : dy,dx -1..1 / skip (0,0) / off-board = 0 /
                  n += cells[..]  (cells are 0/1, not ASCII)
   6. STEP      : next = calloc / read cells write next /
                  n==3 || (n==2 && alive) / free(cells); cells=next
                  / while (it-- > 0)
   7. FINAL     : free on EVERY exit path / -Wall -Wextra -Werror
                  / valgrind

   THE FOUR THAT BITE:
      buf[i++]            advance before continue
      cells = NULL        before you can fail
      calloc not malloc   dead is zero
      read old, write new two boards or it's generation 1.5
   ============================================================ */