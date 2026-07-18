#include "bsq.h"

int min3(int a, int b, int c) {
	return (a <= b && a <= c) ? a : (b <= c) ? b : c;
}

Map* read_map(char *f) {
	FILE *file = f ? fopen(f, "r") : stdin;
	if (!file) return NULL;

	Map *m = malloc(sizeof(Map));
	if (!m || fscanf(file, "%d %c %c %c\n", &m->lines, &m->empty, &m->obstacle, &m->full) != 4
		|| m->empty == m->obstacle || m->empty == m->full || m->obstacle == m->full
		|| m->lines <= 0 || !(m->map = malloc(m->lines * sizeof(char*)))) {
		if (m) free(m);
		if (f) fclose(file);
		return NULL;
	}

	for (int i = 0; i < m->lines; i++) {
		char *line = NULL;
		size_t len = 0;
		ssize_t r = getline(&line, &len, file);
		if (r == -1) {
			while (i--) free(m->map[i]);
			free(m->map);
			free(m);
			if (f) fclose(file);
			return NULL;
		}
		if (line[r - 1] == '\n') line[--r] = 0;
		if (r > 0 && line[r - 1] == '\r') line[--r] = 0;
		if (i == 0) m->width = r;
		else if (r != m->width) {
			while (i >= 0) free(m->map[i--]);
			free(line);
			free(m->map);
			free(m);
			if (f) fclose(file);
			return NULL;
		}
		m->map[i] = line;
	}
	if (f) fclose(file);
	return m;
}

int validate_map(Map *m) {
	if (!m || m->lines <= 0 || m->width <= 0) return 0;
	for (int i = 0; i < m->lines; i++)
		for (int j = 0; j < m->width; j++)
			if (m->map[i][j] != m->empty && m->map[i][j] != m->obstacle)
				return 0;
	return 1;
}

void solve_bsq(Map *m) {
	int **dp = malloc(m->lines * sizeof(int*));
	if (!dp) return;
	for (int i = 0; i < m->lines; i++)
		if (!(dp[i] = calloc(m->width, sizeof(int)))) {
			while (i--) free(dp[i]);
			free(dp);
			return;
		}

	int max = 0, bi = 0, bj = 0;
	for (int i = 0; i < m->lines; i++) {
		for (int j = 0; j < m->width; j++) {
			dp[i][j] = (m->map[i][j] == m->obstacle) ? 0 : (i == 0 || j == 0) ? 1 :
						min3(dp[i-1][j], dp[i][j-1], dp[i-1][j-1]) + 1;
			if (dp[i][j] > max) {
				max = dp[i][j];
				bi = i;
				bj = j;
			}
		}
	}

	for (int i = bi - max + 1; i <= bi; i++)
		for (int j = bj - max + 1; j <= bj; j++)
			m->map[i][j] = m->full;

	for (int i = 0; i < m->lines; i++) free(dp[i]);
	free(dp);
}

void free_map(Map *m) {
	if (!m) return;
	if (m->map) {
		for (int i = 0; i < m->lines; i++)
			if (m->map[i]) free(m->map[i]);
		free(m->map);
	}
	free(m);
}

void process_file(char *f) {
	Map *m = read_map(f);
	if (!m || !validate_map(m)) {
		fprintf(stderr, "map error\n");
		if (m) free_map(m);
		return;
	}
	solve_bsq(m);
	for (int i = 0; i < m->lines; i++)
		fprintf(stdout, "%s\n", m->map[i]);
	free_map(m);
}

int main(int ac, char **av) {
	if (ac == 1)
		process_file(NULL);
	else
		for (int i = 1; i < ac; i++)
			process_file(av[i]);
	return 0;
}
