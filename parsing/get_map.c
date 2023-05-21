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

int	get_map(char **split, t_parser *elements)
{
	int	i;
	int	len;
	int	biggest;
	int	index;

	len = 0;
	i = 0;
	index = 0;
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
	elements->map[i] = NULL;
	return (0);
}