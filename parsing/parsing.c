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
	printf("%s\n", *content);
	close(fd);
}

void parser(char *file)
{
	char	*content;
	int		skip;

	read_file_to_content(file, &content);
	skip = set_elements(content);
	get_map(content);
	free(content);
}