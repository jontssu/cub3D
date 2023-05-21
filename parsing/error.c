#include "cub3d.h"

int	error_argument_count(void)
{
	write(2, "Error\nIncorrect amount of arguments\n", 36);
	return (1);
}

void	error_in_colors(void)
{
	write(2, "Error\nInvalid colors\n", 21);
	//free
	exit(-1);
}

void	error_in_path(void)
{
	write(2, "Error\nIncorrect path\n", 21);
	//free
	exit(-1);
}

void	error_no_color_setting(void)
{
	write(2, "Error\nMissing color setting\n", 28);
	//free
	exit(-1);
}