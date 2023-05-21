#include "cub3d.h"

void	set_int_array(char *str, int *int_arr)
{
	char	**split;

	split = ft_split(str, ',');
	int_arr[0] = ft_atoi(split[0]);
	int_arr[1] = ft_atoi(split[1]);
	int_arr[2] = ft_atoi(split[2]);
	free_double_pointer(split);
}

int	set_elements(char **split, t_parser *elements)
{
	int	i;

	i = -1;
	while (split[++i])
	{
		if (ft_strncmp(split[i], "NO./", 4) == 0)
			elements->north = ft_strdup(&split[i][4]);
		else if (ft_strncmp(split[i], "SO./", 4) == 0)
			elements->south = ft_strdup(&split[i][4]);
		else if (ft_strncmp(split[i], "WE./", 4) == 0)
			elements->west = ft_strdup(&split[i][4]);
		else if (ft_strncmp(split[i], "EA./", 4) == 0)
			elements->east = ft_strdup(&split[i][4]);
		else if (split[i][0] == 'F' && ft_isdigit(split[i][1]))
			set_int_array(&split[i][1], elements->floor);
		else if (split[i][0] == 'C' && ft_isdigit(split[i][1]))
			set_int_array(&split[i][1], elements->ceiling);
	}
	return (0);
}

int	check_elements(t_parser *elements)
{
	return (0);
}