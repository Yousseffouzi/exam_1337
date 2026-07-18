#ifndef BSQ_H
#define BSQ_H

#include <stdio.h>
#include <stdlib.h>

typedef struct {
	int lines, width;
	char empty, obstacle, full, **map;
} Map;

Map* read_map(char *f);
int validate_map(Map *m);
void solve_bsq(Map *m);
void free_map(Map *m);
void process_file(char *f);
int min3(int a, int b, int c);

#endif
