#ifndef CUB3D_H
# define CUB3D_H
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
}	t_parser;

//Parser
int		parser(char *file, t_parser *elements);
void	check_config_file_name(char *file);
int		set_elements(char **split, t_parser *elements);
void	check_elements(t_parser *elements);
int		get_map(char **split, t_parser *elements);
void	map_check(t_parser *elements);

//Error handling
int		error_argument_count(void);
void	error_cub_file(void);
void	error_in_colors(void);
void	error_in_path(void);
void	error_no_color_setting(void);

//Helpers
void	free_double_pointer(char **array);
#endif
	