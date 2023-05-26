/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jole <jole@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 19:39:14 by jole              #+#    #+#             */
/*   Updated: 2023/05/25 19:56:37 by jole             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	main(int argc, char **argv)
{
	t_parser	elements;

	if (argc != 2)
		error_invalid_input(1);
	parser(argv[1], &elements);
	free_elements(&elements);
	return (0);
}
