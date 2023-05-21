#include "cub3d.h"

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

char	**remove_spaces_foreach(char **split)
{
	int	i;

	i = -1;
	while (split[++i] && i < 6)
		split[i] = remove_spaces(split[i]);
	return (split);
}

void parser(char *file)
{
	char	*content;
	char	**split;

	//filename check .cub
	read_file_to_content(file, &content);
	split = ft_split(content, '\n');	
	split = remove_spaces_foreach(split);
	set_elements(split);
	//get_map(content);
	int i = 0;
	while (split[i])
		printf("%s\n", split[i++]);
	free(content);
	free(split);
}