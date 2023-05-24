#include "parsing.h"

void	error_invalid_char(void)
{
	ft_putstr_fd("Error\nInvalid character found in map\n", 2);
	//free
	exit(-1);
}

void	error_start_position(int count)
{
	if (count)
		ft_putstr_fd("Error\ntoo many starting positions\n", 2);
	else
		ft_putstr_fd("Error\nNo starting position\n", 2);
	//free
	exit(-1);
}

void	error_map_open(void)
{
	ft_putstr_fd("Error\nMap was open\n", 2);
	//free
	exit(-1);
}