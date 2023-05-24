#include "parsing.h"

void	map_check(t_parser *elements)
{
	valid_chars_check(elements);
	flood_fill(elements, elements->start_y, elements->start_x);
}