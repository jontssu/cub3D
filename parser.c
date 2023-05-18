void parser(char *file)
{
	char	*content;

	read_file_to_content(file, &content);
}

void	read_file_to_content(char *file, char **content)
{
	char	buf[1024];
	int		read_val;
	int		fd;

	fd = open(file, O_RDONLY);
	while (read_val > 0)
	{

	}
}