#include "parsing.h"

void	valid_start(t_parser *elements)
{
	int		i;
	int		j;
	int		count;

	i = 0;
	count = 0;
	while (elements->map[i])
	{
		j = 0;
		while (elements->map[i][j])
		{
			if (elements->map[i][j] == 'N' || elements->map[i][j] == 'S' || \
			elements->map[i][j] == 'W' || elements->map[i][j] == 'E')
			{
				count++;
				elements->orientation = elements->map[i][j];
				elements->start_x = j; 
				elements->start_y = i; 
			}
			if (count > 1)
				error_invalid_map(1);
			j++;
		}
		i++;
	}
	if (count < 1)
		error_invalid_map(2);
}

void	valid_start_position(t_parser *elements, int y, int x)
{
	if (x == elements->max_heigth - 1 || y == elements->max_width - 1)
	{
		write(2, "here\n", 5);
		error_invalid_map(7);
	}
	/*else if (elements->map[y - 1][x] != 'X' && elements->map[y - 1][x + 1] \
	!= 'X' && elements->map[y][x + 1] != 'X' && elements->map[y + 1][x + 1] \
	!= 'X' && elements->map[y + 1][x] != 'X' && elements->map[y + 1][x - 1] \
	!= 'X' && elements->map[y][x - 1] != 'X' && elements->map[y - 1][x - 1] \
	!= 'X') 
		return;*/
}

void	valid_chars_check(t_parser *elements)
{
	int	i;
	int	j;

	i = 0;
	while (elements->map[i])
	{
		j = 0;
		while (elements->map[i][j])
		{
			if (elements->map[i][j] != 'X' && elements->map[i][j] != '1' && \
			elements->map[i][j] != '0' && elements->map[i][j] != 'N' && \
			elements->map[i][j] != 'S' && elements->map[i][j] != 'W' && \
			elements->map[i][j] != 'E')
				error_invalid_map(3);
			j++;
		}
		i++;
	}
	valid_start(elements);
	valid_start_position(elements, elements->start_y, elements->start_x);
}