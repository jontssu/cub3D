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
	int		floor[3];
	int		ceiling[3];
	char	**map;
}	t_parser;

//Parser
int	parser(char *file, t_parser *elements);
int	set_elements(char **split, t_parser *elements);

//Error handling
int	error_argument_count(void);

//Helpers
void	free_double_pointer(char **array);
#endif