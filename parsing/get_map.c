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

	len = 0;
	while (split[len])
		len++;
	i = 0;
	elements->map = malloc((len + 1) * sizeof(char *));
	while (i < len)
	{
		elements->map[i] = malloc((get_biggest_strlen(split) + 1) * sizeof(char));
		elements->map[i] = ft_strdup(split[i]);
		i++;
	}
	return (0);
}