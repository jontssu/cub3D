#include "cub3d.h"

void	free_double_pointer(char **array)
{
	int	i;

	i = 0;
	while (array[i])
		free(array[i++]);
	free(array);
}

void	read_file_to_content(char *file, char **content)
{
	char	*line;
	char	*tmp;
	int		fd;

	*content = ft_strdup("");
	fd = open(file, O_RDONLY);
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break;
		tmp = *content;
		*content = ft_strjoin(tmp, line);
		free(line);
		free(tmp);
	}
	//printf("%s\n", *content);
	close(fd);
}

char	*remove_spaces(char *string)
{
	int	i;
	int	j;
	int	check;

	i = 0;
	while (string[i])
	{
		check = 0;
		if (string[i] == ' ')
		{
			j = i;
			while (string[j - 1])
			{
				string[j] = string[j + 1];
				j++;
			}
			check = 1;
		}
		if (check == 0)
			i++;
	}
	return (string);
}

char	**remove_spaces_from_elements(char **split)
{
	int	i;

	i = -1;
	while (split[++i] && i < 6)
		split[i] = remove_spaces(split[i]);
	return (split);
}

int	parser(char *file, t_parser *elements)
{
	char	*content;
	char	**split;

	check_config_file_name(file);
	read_file_to_content(file, &content);
	split = ft_split(content, '\n');	
	split = remove_spaces_from_elements(split);
	set_elements(split, elements);
	check_elements(elements);
	//get_map(content);
	//int i = 0;
	//while (split[i])
		//printf("%s\n", split[i++]);
	printf("ELEMENT: %s\n", elements->north);
	printf("ELEMENT: %s\n", elements->south);
	printf("ELEMENT: %s\n", elements->west);
	printf("ELEMENT: %s\n", elements->east);
	printf("ELEMENT: %d\n", elements->floor[0]);
	printf("ELEMENT: %d\n", elements->floor[1]);
	printf("ELEMENT: %d\n", elements->floor[2]);
	printf("ELEMENT: %d\n", elements->ceiling[0]);
	printf("ELEMENT: %d\n", elements->ceiling[1]);
	printf("ELEMENT: %d\n", elements->ceiling[2]);
	free(content);
	free_double_pointer(split);
	return (0);
}