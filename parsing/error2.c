#include "cub3d.h"

void	error_invalid_char(void)
{
	write(2, "Error\nInvalid character found in map\n", 37);
	//free
	exit(-1);
}

void	error_start_position(void)
{
	write(2, "Error\nInvalid player position\n", 30);
	//free
	exit(-1);
}