#ifndef CUB3D_H
# define CUB3D_H
# include "libft.h"
# include <stdio.h>
# include <unistd.h>
# include <fcntl.h>

typedef struct s_parser
{
	char	*NO;
	char	*SO;
	char	*WE;
	char	*EA;
	int		F[3];
	int		C[3];
	char	**map;
}	t_parser;

//Parser
void	parser(char *file);

//Error handling
int	error_argument_count(void);
#endif