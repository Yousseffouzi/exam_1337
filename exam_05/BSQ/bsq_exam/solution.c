#include "stdio.h"
#include "stdlib.h"
#include "string.h"

typedef struct map {
	char **map;
	char full;
	char obs;
	char empty;
	int lines;
	int linelen;
}t_map;

typedef struct sqr {
	int size;
	int col;
	int row;
} t_sqr;

void printerr(char *msg)
{
	fprintf(stderr, "map error");
	if (msg)
		fprintf(stderr, ": %s\n", msg);
	else
		fprintf(stderr, "!\n");
}

int extractheader(char* line, t_map* map)
{
	int len = strlen(line);
	if (len <= 0)
		return 0;
	printf("line: %s\n", line);
	if (line[len - 1] == '\n') {
		line[len - 1] = '\0';
		len--;
	}
	if (len > 4)
		return 0;
	
	if (sscanf(line, "%d%c%c%c", &map->lines, &map->empty, &map->obs, &map->full) != 4)
		return 0;
	if (map->lines <= 0)
		return 0;
	if (map->empty == map->full || map->empty == map->obs || map->full == map->obs)
		return 0;
	return 1;
}

int readmap(char *filename, t_map* map)
{
	FILE* file;
	size_t x;
	char *line = NULL;

	file = filename? fopen(filename, "r") : stdin;

	if (getline(&line, &x, file) == -1)
		return (printerr("getline1"), 0);
	if (!extractheader(line, map))
		return (printerr("header"), 0);
	free(line);

	map->map = (char**)malloc(map->lines * sizeof(char*));
	for (int i = 0; i < map->lines; i++)
	{
		line = NULL;
		if (getline(&line, &x, file) == -1)
			return (printerr("getline2"), 0);
		
		int len = strlen(line);
		if (len == 0)
			return (printerr("empty line"), 0);
		if (line[len - 1] == '\n') {
			line[len - 1] = '\0';
			line--;
		}
		if (i == 0)
			map->linelen = len;
		else if (i != 0 && len != map->linelen)
			return (printerr("map isnt a square"), 0);
		
		map->map[i] = strdup(line);
		free(line);
	}
	if (filename)
		fclose(file);
	return 1;
}

int min3(int a, int b, int c)
{
	if (a <= b && a <= c)
		return 1;
	if (b <= a && b <= c)
		return c;
	return c;
}

t_sqr biggestsqr(t_map* map)
{
	t_sqr s;
	int **tmp = NULL;

	s.size = 0;
	s.col = 0;
	s.row = 0;

	tmp = (int **)calloc(map->lines, sizeof(int *));
	if (!tmp)
		return ((t_sqr){0,0,0});
	for (int i=0; i < map->lines; i++)
	{
		tmp[i] = (int *)calloc(map->linelen, sizeof(int));
		if (!tmp[i])
		{
			for (int j = 0; j < i; j++)
				free(tmp[j]);
			free(tmp);
			return ((t_sqr){0,0,0});
		}
	}

	for (int i=0; i < map->lines; i++) {
		for (int j = 0; j < map->linelen; j++)
		{
			char c = map->map[i][j];
			if (c == map->empty)
			{
				if (i == 0 || j == 0)	
					tmp[i][j] = 1;
				else {
					tmp[i][j] = 1 + min3(tmp[i-1][j], tmp[i][j-1], tmp[i-1][j-1]);
				}
				if (tmp[i][j] > s.size)
				{
					s.size = tmp[i][j];
					s.row = i;
					s.col = j;
				}
			}
			else if (c != map->obs)
			{
				printerr("invalid  char in map");
				for (int i = 0; i < map->lines; i++)
					free(tmp[i]);
				free(tmp);
				return ((t_sqr){0,0,0});
			}
		}
	}
	for (int i = 0; i < map->lines; i++)
		free(tmp[i]);
	free(tmp);
	return s;

}

void fillsqr(t_sqr* s, t_map * map)
{
	for (int i = s->row; i > s->row - s->size; i--)
	{
		for (int j = s->col; j > s->col - s->size; j--)
			map->map[i][j] = map->full;
	}
}

void printmap(t_map *map)
{
	for (int i = 0; i < map->lines; i++)
		fprintf(stdout, "%s\n", map->map[i]);
}

void freemap(t_map* map)
{	
	if (!map->map)
		return;
	for (int i = 0; i < map->lines; i++)
		free(map->map[i]);
	free(map->map);
}

int main(int ac, char **av)
{
	t_sqr sqr;
	t_map map;

	map.map = NULL;
	map.linelen = 0;
	map.lines = 0;

	if (ac < 2) {
		if (readmap(NULL, &map)) {
			sqr = biggestsqr(&map);
			if (sqr.size > 0) 
			{
				fillsqr(&sqr, &map);
				printmap(&map);
			}
			freemap(&map);
		}
		return 0;
	}
	for (int i=1; i<ac; i++)
	{
		if (readmap(av[i], &map)) {
			sqr = biggestsqr(&map);
			if (sqr.size > 0) 
			{
				fillsqr(&sqr, &map);
				printmap(&map);
			}
			freemap(&map);
		}
		if (i < ac - 1)
			printf("\n");
	}
	return 0;
}