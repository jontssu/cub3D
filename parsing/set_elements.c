#include "cub3d.h"

int	set_elements(char *content)
{
	int	i;

	i = 0;
	while (content[i])
	{
		if (content[i] == 'N' && content[i + 1] == 'O') 
			set_north(&content[i]);
	}
}