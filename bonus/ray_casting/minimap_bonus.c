/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jole <jole@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 09:48:56 by leklund           #+#    #+#             */
/*   Updated: 2023/06/14 17:28:43 by jole             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D_bonus.h"
#include <string.h>

char	**copy_2d_array(char **arr)
{
	int		rows;
	int		cols;
	char	**copy;
	int		i;

	rows = 0;
	cols = 0;
	while (arr[0][cols])
		cols++;
	while (arr[rows])
		rows++;
	copy = malloc((rows + 1) * sizeof(char *));
	if (copy == NULL)
	{
		fprintf(stderr, "Memory allocation failed.");
		exit(1);
	}
	i = -1;
	while (++i < rows)
	{
		copy[i] = malloc((cols + 1) * sizeof(char));
		if (copy[i] == NULL)
		{
			fprintf(stderr, "Memory allocation failed.");
			exit(1);
		}
		strcpy(copy[i], arr[i]);
	}
	copy[rows] = NULL;
	return (copy);
}

void	render_color(t_player *p, int y, int x, int color)
{
	if (color == 1)
		p->buf[p->count_y + (p->size * (int)(y - (p->pos_y - p->r_size)))] \
		[p->count_x + (p->size * (int)(x - (p->pos_x - p->r_size)))] = 0;
	else if (color == 2)
		p->buf[p->count_y + (p->size * (int)(y - (p->pos_y - p->r_size)))] \
		[p->count_x + (p->size *(int)(x - (p->pos_x - p->r_size)))] = 0x00FFFF;
	else if (color == 3)
		p->buf[p->count_y + (p->size * (int)(y - (p->pos_y - p->r_size)))] \
		[p->count_x + (p->size *(int)(x - (p->pos_x - p->r_size)))] = 0xFF00FF;
	else if (color == 4)
		p->buf[p->count_y + (p->size * (int)(y - (p->pos_y - p->r_size)))] \
		[p->count_x + (p->size *(int)(x - (p->pos_x - p->r_size)))] = 0xFFFFFF;
	else if (color == 5)
		p->buf[p->count_y + (p->size * (int)(y - (p->pos_y - p->r_size)))] \
		[p->count_x + (p->size *(int)(x - (p->pos_x - p->r_size)))] = 0xFF0000;
	else if (color == 6)
		p->buf[p->count_y + (p->size * (int)(y - (p->pos_y - p->r_size)))] \
		[p->count_x + (p->size *(int)(x - (p->pos_x - p->r_size)))] = 200;
	else if (color == 7)
		p->buf[p->count_y + (p->size * (int)(y - (p->pos_y - p->r_size)))] \
		[p->count_x + (p->size *(int)(x - (p->pos_x - p->r_size)))] = 0xFF9999;
}

void	fill_buff_minimap(t_player *p, int y, int x)
{
	p->count_y = 0;
	p->size = (WIDTH / HEIGHT) * 10;
	while (p->count_y++ < 10)
	{
		p->count_x = 0;
		while (p->count_x++ < 10)
		{
			if (y < 0 || y >= p->elements->max_heigth || x >= \
			p->elements->max_width || x < 0)
				render_color(p, y, x, 1);
			else if (x == (int)p->pos_x && y == (int)p->pos_y)
				render_color(p, y, x, 2);
			else if (p->cpy_map[y][x] == '/')
				render_color(p, y, x, 3);
			else if (p->cpy_map[y][x] == 'I')
				render_color(p, y, x, 4);
			else if (p->cpy_map[y][x] == '.')
				render_color(p, y, x, 5);
			else if (p->cpy_map[y][x] == 'D')
				render_color(p, y, x, 6);
			else if (p->cpy_map[y][x] == 'O')
				render_color(p, y, x, 7);
		}
	}
}

void	minimap(t_player *p)
{
	int	y;
	int	x;

	p->r_size = 7;
	if (p->elements->max_heigth < 7)
		p->r_size = p->elements->max_heigth - 2;
	else if (p->elements->max_width < 7)
		p->r_size = p->elements->max_width - 2;
	y = p->pos_y - p->r_size;
	while (y <= p->pos_y + p->r_size)
	{
		x = p->pos_x - p->r_size;
		while (x <= p->pos_x + p->r_size)
			fill_buff_minimap(p, y, x++);
		y++;
	}
}
