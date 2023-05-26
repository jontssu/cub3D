#include "parsing.h"

void	free_elements(t_parser *elements)
{
	free(elements->north);
	free(elements->south);
	free(elements->west);
	free(elements->east);
	free_double_pointer(elements->map);
}

void	free_double_pointer(char **array)
{
	int	i;

	i = 0;
	while (array[i])
		free(array[i++]);
	free(array);
}