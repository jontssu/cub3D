#include "cub3D.h"

void	valid_start(t_parser *elements)
{
	int	i;
	int	j;
	int	count;

	i = 0;
	count = 0;
	while (elements->map[i])
	{
		j = 0;
		while (elements->map[i][j])
		{
			if (elements->map[i][j] == 'N' || elements->map[i][j] == 'S' || \
			elements->map[i][j] == 'W' || elements->map[i][j] == 'E')
				count++;
			if (count > 1)
				error_start_position();
			j++;
		}
		i++;
	}
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
				error_invalid_char();
			j++;
		}
		i++;
	}
	valid_start(elements);
}