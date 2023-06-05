/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_chars_check_bonus.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leklund <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/04 06:33:55 by leklund           #+#    #+#             */
/*   Updated: 2023/06/04 06:33:57 by leklund          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing_bonus.h"

void	valid_start(t_parser *elements, int i, int count)
{
	int		j;

	while (elements->map[i])
	{
		j = 0;
		while (elements->map[i][j])
		{
			if (elements->map[i][j] == 'N' || elements->map[i][j] == 'S' || \
			elements->map[i][j] == 'W' || elements->map[i][j] == 'E')
			{
				count++;
				elements->orientation = elements->map[i][j];
				elements->start_x = j;
				elements->start_y = i;
			}
			if (count > 1)
				error_invalid_map(elements, 1);
			j++;
		}
		i++;
	}
	if (count < 1)
		error_invalid_map(elements, 2);
}

void	valid_start_position(t_parser *elements, int y, int x)
{
	if (y == elements->max_heigth - 1 || x == elements->max_width - 1 \
	|| x == 0 || y == 0)
		error_invalid_map(elements, 7);
	else if (elements->map[y - 1][x] != 'X' && elements->map[y - 1][x + 1] \
	!= 'X' && elements->map[y][x + 1] != 'X' && elements->map[y + 1][x + 1] \
	!= 'X' && elements->map[y + 1][x] != 'X' && elements->map[y + 1][x - 1] \
	!= 'X' && elements->map[y][x - 1] != 'X' && elements->map[y - 1][x - 1] \
	!= 'X')
		return ;
	error_invalid_map(elements, 7);
}

void	valid_chars_check(t_parser *elements)
{
	int	i;
	int	j;

	i = 0;
	while (elements->map[i])
	{
		j = 0;
		while (elements->map[i][j])
		{
			if (elements->map[i][j] != 'X' && elements->map[i][j] != '1' && \
			elements->map[i][j] != '0' && elements->map[i][j] != 'N' && \
			elements->map[i][j] != 'S' && elements->map[i][j] != 'W' && \
			elements->map[i][j] != 'E' && elements->map[i][j] != 'D')
				error_invalid_map(elements, 3);
			j++;
		}
		i++;
	}
	valid_start(elements, 0, 0);
	valid_start_position(elements, elements->start_y, elements->start_x);
}
