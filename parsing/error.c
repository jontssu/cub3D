#include "parsing.h"

int	error_argument_count(void)
{
	ft_putstr_fd("Error\nIncorrect amount of arguments\n", 2);
	return (1);
}

void	error_cub_file(void)
{
	ft_putstr_fd("Error\nInvallid config file\n", 2);
	//free
	exit(-1);
}

void	error_in_colors(void)
{
	ft_putstr_fd("Error\nInvalid colors\n", 2);
	//free
	exit(-1);
}

void	error_in_path(void)
{
	ft_putstr_fd("Error\nIncorrect path for elements\n", 2);
	//free
	exit(-1);
}

void	error_no_color_setting(void)
{
	ft_putstr_fd("Error\nMissing color setting\n", 2);
	//free
	exit(-1);
}

void	error_invalid_map(int error)
{
	if (error == 1)
		ft_putstr_fd("Error\ntoo many starting positions\n", 2);
	else if (error == 2)
		ft_putstr_fd("Error\nNo starting position\n", 2);
	else if (error == 3)
		ft_putstr_fd("Error\nInvalid character found in map\n", 2);
	else if (error == 4)
		ft_putstr_fd("Error\nMap was open\n", 2);
	else if (error == 5)
		ft_putstr_fd("Error\nPart of the map was not connected\n", 2);
	else if (error == 6)
		ft_putstr_fd("Error\nInvalid map component\n", 2);
	else if (error == 7)
		ft_putstr_fd("Error\nStarting position is invalid\n", 2);
	//free
	exit(-1);
}