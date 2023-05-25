/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jole <jole@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 19:39:14 by jole              #+#    #+#             */
/*   Updated: 2023/05/25 19:50:39 by jole             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	free_elements(t_parser *elements)
{
	free(elements->north);
	free(elements->south);
	free(elements->west);
	free(elements->east);
	free_double_pointer(elements->map);
}

int	main(int argc, char **argv)
{
	t_parser	elements;

	if (argc != 2)
		error_invalid_input(1);
	parser(argv[1], &elements);
	free_elements(&elements);
	return (0);
}
