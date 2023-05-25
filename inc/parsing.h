#ifndef PARSING_H
# define PARSING_H
# include "libft.h"
# include <stdio.h>
# include <unistd.h>
# include <fcntl.h>

typedef struct s_parser
{
	char	*north;
	char	*south;
	char	*west;
	char	*east;
	int		floor[4];
	int		ceiling[4];
	char	**map;
	char	orientation;
	int		start_x;
	int		start_y;
	int		max_width;
	int		max_heigth;
}	t_parser;

//Parser
int		parser(char *file, t_parser *elements);
void	check_config_file_name(char *file);
int		set_elements(char **split, t_parser *elements);
void	check_elements(t_parser *elements);
int		get_map(char **split, t_parser *elements);
void	fill_with_x(int max_size, t_parser *elements);

//Map check
void	map_check(t_parser *elements);
void	valid_chars_check(t_parser *elements);
void	flood_fill(t_parser *elements, int y, int x);

//Error handling
void	error_invalid_input(int error);
void	error_malloc(char *content);
void	error_in_colors(t_parser *elements, char **split, char **split2);
void	error_invalid_configuration(t_parser *elements, int error);
void	error_invalid_map(t_parser *elements, int error);

//Helpers
void	free_double_pointer(char **array);
void	free_elements(t_parser *elements);
#endif
	