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
void	parser(char *file);
int		set_elements(char **split);

//Error handling
int	error_argument_count(void);
#endif