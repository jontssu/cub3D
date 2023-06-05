/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leklund <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/04 06:33:13 by leklund           #+#    #+#             */
/*   Updated: 2023/06/04 06:33:14 by leklund          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "parsing_bonus.h"

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
