#include "cub3d.h"

void	map_check(t_parser *elements)
{
	int	i;
	int	j;

	i = 0;
	while (elements->map[i]) 
	{
		j = 0;
		while (elements->map[i][j])
		{
			if (elements->map[i][j] == ' ')
				elements->map[i][j] = 'X';
			j++;
		}
		i++;
	}
}