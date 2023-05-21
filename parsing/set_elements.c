#include "cub3d.h"

int	check_for_element(char *str, char *check)
{
	int	i;

	i = 0;
	if (strncmp(str, check, 4))
		return (1);
	while (str[i])
	{
		if (str[i])
	}
}

int	set_elements(char **split)
{
	int	i;

	i = -1;
	while (split[++i])
	{
		if (check_for_element(split[i], "NO./"))
		{

		}
		/*if (!ft_strncmp(split[i], "NO ./", 5) || !ft_strncmp(split[i], "NO./", 4))
			printf("NORTH FOUND: %s\n", split[i]);
		if (!ft_strncmp(split[i], "SO ./", 5) || !ft_strncmp(split[i], "SO./", 4))
			printf("SOUTH FOUND: %s\n", split[i]);
		if (!ft_strncmp(split[i], "WE ./", 5) || !ft_strncmp(split[i], "WE./", 4))
			printf("WEST FOUND: %s\n", split[i]);
		if (!ft_strncmp(split[i], "EA ./", 5) || !ft_strncmp(split[i], "EA./", 4))
			printf("EAST FOUND: %s\n", split[i]);
		if (!ft_strncmp(split[i], "F ", 2))
			printf("FLOOR FOUND: %s\n", split[i]);
		if (!ft_strncmp(split[i], "C ", 2))
			printf("CEILING FOUND: %s\n", split[i]);*/
	}
	printf("\n-----\n");
	return (0);
}