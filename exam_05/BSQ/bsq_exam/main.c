#include "bsq.h"

int main(int argc, char **argv)
{
	t_map map;
	t_square sq;
	int i;

	if (argc < 2)
	{
		if (read_map(NULL, &map))
		{
			sq = find_biggest_square(&map);
			if (sq.size > 0)
			{
				fill_square(&map, sq);
				print_map(&map);
			}
			free_map(&map);
		}
		return (0);
	}
	for (i = 1; i < argc; i++)
	{
		if (read_map(argv[i], &map))
		{
			sq = find_biggest_square(&map);
			if (sq.size > 0)
			{
				fill_square(&map, sq);
				print_map(&map);
			}
			free_map(&map);
		}
		if (i < argc - 1)
			fprintf(stdout, "\n");
	}
	return (0);
}
