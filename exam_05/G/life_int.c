#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

int main(int ac, char **av)
{
	if (ac != 4)
		return 1;

	int w = atoi(av[1]);
	int h = atoi(av[2]);
	int ret = atoi(av[3]);
	int x = 0, y = 0, pen = 0;
	char c;
	int board[h][w];
	int next[h][w];

	for (int i = 0; i < h; i++)
		for (int j = 0; j < w; j++)
			board[i][j] = 0;

	while (read(0, &c, 1) == 1)
	{
		if (c == 'w' && y > 0)
			y--;
		else if (c == 's' && y < h - 1)
			y++;
		else if (c == 'a' && x > 0)
			x--;
		else if (c == 'd' && x < w - 1)
			x++;
		else if (c == 'x')
			pen = !pen;
		if (pen)
			board[y][x] = 1;
	}

	while (ret--)
	{
		for (int i = 0; i < h; i++)
		{
			for (int j = 0; j < w; j++)
			{
				int n = 0;
				for (int y = -1; y <= 1; y++)
				{
					for (int x = -1; x <= 1; x++)
						if ((y || x) && i + y > -1 && i + y < h && j + x > -1 && j + x < w)
							n += board[i + y][j + x];
				}
				if (board[i][j])
					next[i][j] = (n == 2 || n == 3);
				else
					next[i][j] = (n == 3);
			}
		}
		for (int i = 0; i < h; i++)
			for (int j = 0; j < w; j++)
				board[i][j] = next[i][j];
	}
	for (int i = 0; i < h; i++)
	{
		for (int j = 0; j < w; j++)
			putchar(board[i][j] ? 'O' : ' ');
		putchar('\n');
	}
	return 0;
}