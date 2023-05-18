#ifndef CUB3D_H
# define CUB3D_H
# include <stdio.h>

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

#endif