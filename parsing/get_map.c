#include "cub3d.h"

int	get_biggest_strlen(char **split)
{
	int	i;
	int	len;
	int	biggest_len;

	i = -1;
	biggest_len = 0;
	while (split[++i])
	{
		len = ft_strlen(split[i]);
		if (len > biggest_len)
			biggest_len = len;
	}
	return (biggest_len);
}

void	fill_with_x(int max_size, t_parser *elements)
{
	int	i;
	int	j;

	i = 0;
	while (elements->map[i])
	{
		j = max_size - 1;
		while (j)
		{
			if (elements->map[i][j] != '0' && elements->map [i][j] != '1')
				elements->map[i][j] = 'X';	
			j--;
		}
		if (elements->map[i][j] != '0' && elements->map [i][j] != '1')
			elements->map[i][j] = 'X';	
		i++;
	}
}

int	get_map(char **split, t_parser *elements)
{
	int	i;
	int	len;
	int	biggest;

	len = 0;
	i = 0;
	biggest = get_biggest_strlen(split);
	while (split[len])
		len++;
	elements->map = ft_calloc(len + 1, sizeof(char *));
	while (i < len)
	{
		elements->map[i] = ft_calloc(biggest + 1, sizeof(char));
		ft_memcpy(elements->map[i], split[i], ft_strlen(split[i]));
		i++;
	}
	fill_with_x(biggest, elements);
	elements->map[i] = NULL;
	return (0);
}