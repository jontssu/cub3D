/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flood_fill_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jole <jole@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/04 06:32:59 by leklund           #+#    #+#             */
/*   Updated: 2023/06/14 17:24:54 by jole             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing_bonus.h"

void	check_edges(t_parser *elements, int y, int x)
{
	if (x == 0 && y <= (elements->max_heigth - 1) && \
	elements->map[y][x] == '0')
		error_invalid_map(elements, 4);
	else if (y == 0 && x <= (elements->max_width - 1) && \
	elements->map[y][x] == '0')
		error_invalid_map(elements, 4);
	else if (x == (elements->max_width - 1) && y < (elements->max_heigth - 1) \
	&& elements->map[y][x] == '0')
		error_invalid_map(elements, 4);
	else if (x < (elements->max_width - 1) && y == (elements->max_heigth - 1) \
	&& elements->map[y][x] == '0')
		error_invalid_map(elements, 4);
}

int	check_zero_surroundings(t_parser *elements, int y, int x)
{
	if (elements->map[y - 1][x] != 'X' && elements->map[y - 1][x + 1] != 'X' \
	&& elements->map[y][x + 1] != 'X' && elements->map[y + 1][x + 1] != 'X' \
	&& elements->map[y + 1][x] != 'X' && elements->map[y + 1][x - 1] != 'X' \
	&& elements->map[y][x - 1] != 'X' && elements->map[y - 1][x - 1] != 'X')
		return (0);
	return (1);
}

void	check_if_fill(t_parser *elements, int y, int x)
{
	if (y < 0 || x < 0 || y > elements->max_heigth - 1 || \
	x > elements->max_width - 1)
		return ;
	check_edges(elements, y, x);
	if (elements->map[y][x] == '1')
	{
		elements->map[y][x] = 'I';
		flood_fill(elements, y, x);
	}
	if (elements->map[y][x] == '0')
	{
		if (y == elements->max_heigth || x == elements->max_width || \
		check_zero_surroundings(elements, y, x))
			error_invalid_map(elements, 4);
		elements->map[y][x] = '.';
		flood_fill(elements, y, x);
	}
}

void	flood_fill(t_parser *elements, int y, int x)
{
	check_if_fill(elements, y + 1, x);
	check_if_fill(elements, y, x + 1);
	check_if_fill(elements, y - 1, x);
	check_if_fill(elements, y, x - 1);
}
