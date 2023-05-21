#include "cub3d.h"

void	check_config_file_name(char *file)
{
	int	len;

	len = ft_strlen(file);
	if (file[len - 1] == 'b' && file[len - 2] == 'u' && \
	file[len - 3] == 'c' && file[len - 4] == '.')
	{
		len = open(file, O_RDONLY);
		if (len != -1)
			return;
	}
	error_cub_file();
}

void	set_int_array(char *str, int *int_arr)
{
	char	**split;

	split = ft_split(str, ',');
	int_arr[0] = ft_atoi(split[0]);
	if (int_arr[0] > 255 || int_arr[0] < 0)
		error_in_colors();
	int_arr[1] = ft_atoi(split[1]);
	if (int_arr[1] > 255 || int_arr[1] < 0)
		error_in_colors();
	int_arr[2] = ft_atoi(split[2]);
	if (int_arr[2] > 255 || int_arr[2] < 0 || split[3])
		error_in_colors();
	int_arr[3] = 1;
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
		printf("IM HERE\n");
	}
	return (0);
}

void	check_path(char *path)
{
	int	fd;

	fd = open(path, O_RDONLY);
	if (fd == -1)
		error_in_path();
}

void	check_elements(t_parser *elements)
{
	check_path(elements->north);
	check_path(elements->south);
	check_path(elements->west);
	check_path(elements->east);
	if (elements->ceiling[3] == 0 || elements->floor[3] == 0)
		error_no_color_setting();
}