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