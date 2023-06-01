/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jole <jole@student.hive.fi>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 18:36:32 by jole              #+#    #+#             */
/*   Updated: 2023/06/01 18:36:33 by jole             ###   ########.fr       */
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

void	free_double_pointer(char **array)
{
	int	i;

	i = 0;
	while (array[i])
		free(array[i++]);
	free(array);
}
