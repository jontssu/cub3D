#include "parsing.h"

int	check_zero_surroundings(t_parser *elements, int y, int x)
{
	if (elements->map[y - 1][x] != 'X' && elements->map[y - 1][x + 1] != 'X' \
	&& elements->map[y][x + 1] != 'X' && elements->map[y + 1][x + 1] != 'X' \
	&& elements->map[y + 1][x] != 'X' && elements->map[y + 1][x - 1] != 'X' \
	&& elements->map[y][x - 1] != 'X' && elements->map[y - 1][x - 1] != 'X') 
		return (0);
	return (1);
}

int	check_if_fill(t_parser *elements, int y, int x)
{
	printf("CHECKING:%d,%d\n", y, x);
	if (y < 0 || x < 0 || y >= elements->max_heigth || x > elements->max_width)
		return (0);
	if (elements->map[y][x] == '1')
	{
		elements->map[y][x] = 'I';
		flood_fill(elements, y, x);
	}
	if (elements->map[y][x] == '0')
	{
		if (y == elements->max_heigth || x == elements->max_width || \
		check_zero_surroundings(elements, y, x))
			error_map_open();
		elements->map[y][x] = '.';
		flood_fill(elements, y, x);
	}
	return (0);
}

void	flood_fill(t_parser *elements, int y, int x)
{
	check_if_fill(elements, y + 1, x);
	check_if_fill(elements, y, x + 1);
	check_if_fill(elements, y - 1, x);
	check_if_fill(elements, y, x - 1);
}