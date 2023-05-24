#include "parsing.h"

void	flood_fill_check(t_parser *elements)
{
	int	i;
	int	j;

	i = 0;
	while (elements->map[i])
	{
		j = 0;
		while (elements->map[i][j])
		{
			if (elements->map[i][j] == '0' || elements->map[i][j] == '1')
				error_invalid_map(5);
			else if (elements->map[i][j] != 'X' && elements->map[i][j] != 'I' \
			&& elements->map[i][j] != '.' && elements->map[i][j] != \
			elements->orientation)
				error_invalid_map(6);
			j++;
		}
		i++;
	}
}

void	map_check(t_parser *elements)
{
	valid_chars_check(elements);
	flood_fill(elements, elements->start_y, elements->start_x);
	flood_fill_check(elements);
}