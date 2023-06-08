/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_casting_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jole <jole@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/04 06:32:26 by leklund           #+#    #+#             */
/*   Updated: 2023/06/07 15:59:57by jole             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



#include "cub3D_bonus.h"

void	calc_line(t_dda *dda)
{
	if (dda->side == 0)
	{
		dda->perp_wall_dist = (dda->tot_dist_x - dda->delta_dist_x);
	}
	else
	{
		dda->perp_wall_dist = (dda->tot_dist_y - dda->delta_dist_y);
	}
	dda->line_height = (int)(HEIGHT / dda->perp_wall_dist);
	dda->draw_start = -dda->line_height / 2 + HEIGHT / 2;
	if (dda->draw_start < 0)
		dda->draw_start = 0;
	dda->draw_end = dda->line_height / 2 + HEIGHT / 2;
	if (dda->draw_end >= HEIGHT)
		dda->draw_end = HEIGHT;
	
}


void	digital_differential_analysis(t_player *P, t_dda *dda)
{
	while (dda->hit == 0)
	{
		if (dda->tot_dist_x < dda->tot_dist_y)
		{
			dda->tot_dist_x += dda->delta_dist_x;
			dda->map_x += dda->step_x;
			dda->side = 0;
		}
		else
		{
			dda->tot_dist_y += dda->delta_dist_y;
			dda->map_y += dda->step_y;
			dda->side = 1;
		}
		if (P->map[dda->map_y][dda->map_x] == 'I')
			dda->hit = 1;
		else if (P->map[dda->map_y][dda->map_x] == 'D')
			dda->hit = 2;
		else if (P->map[dda->map_y][dda->map_x] == 'O')
			dda->hit = 3;
		if (!dda->hit)
			P->cpy_map[dda->map_y][dda->map_x] = '/';
	}
}

void	start_dir_len(t_player *P, t_dda *dda)
{
	if (dda->ray_dir_x < 0)
	{
		dda->step_x = -1;
		dda->tot_dist_x = (P->pos_x - dda->map_x) * dda->delta_dist_x;
	}
	else
	{
		dda->step_x = 1;
		dda->tot_dist_x = (dda->map_x + 1.0 - P->pos_x) * dda->delta_dist_x;
	}
	if (dda->ray_dir_y < 0)
	{
		dda->step_y = -1;
		dda->tot_dist_y = (P->pos_y - dda->map_y) * dda->delta_dist_y;
	}
	else
	{
		dda->step_y = 1;
		dda->tot_dist_y = (dda->map_y + 1.0 - P->pos_y) * dda->delta_dist_y;
	}
}

void	make_screen(t_player *player, t_dda *dda)
{
	dda->hit = 0;
	dda->map_x = (int)player->pos_x;
	dda->map_y = (int)player->pos_y;
	dda->camera_x = (2 * dda->x / ((double)WIDTH - 1) - 1) * -1;
	dda->ray_dir_x = player->dir_x + (player->plane_x * dda->camera_x);
	dda->ray_dir_y = player->dir_y + (player->plane_y * dda->camera_x);
	if (dda->ray_dir_x == 0)
		dda->delta_dist_x = 1e30;
	else
		dda->delta_dist_x = fabs(1.0 / dda->ray_dir_x);
	if (dda->ray_dir_y == 0)
		dda->delta_dist_y = 1e30;
	else
		dda->delta_dist_y = fabs(1.0 / dda->ray_dir_y);
	start_dir_len(player, dda);
	digital_differential_analysis(player, dda);
	calc_line(dda);
	texture(player, dda);
	dda->hit = 0;
	dda->x++;
}

void	fill_buff_minimap(t_player *p, int y, int x)
{
	int	count_y;
	int	count_x;
	int	size;

	count_y = 0;
	size = (WIDTH / HEIGHT) * 10;
	while (count_y++ < 10)
	{
		count_x = 0;
		while (count_x++ < 10)
		{
			if (y < 0 || y >= p->elements->max_heigth || x >= \
			p->elements->max_width || x < 0)
				p->buf[count_y + (size * (int)(y - (p->pos_y - MAP_SIZE)))] \
				[count_x + (size *(int)(x - (p->pos_x - MAP_SIZE)))] = 0;
			else if (x == (int)p->pos_x && y == (int)p->pos_y)
				p->buf[count_y + (size * (int)(y - (p->pos_y - MAP_SIZE)))] \
				[count_x + (size * (int)(x - (p->pos_x - MAP_SIZE)))] = 0x00FFFF;	
			else if (p->cpy_map[y][x] == '/')
				p->buf[count_y + (size * (int)(y - (p->pos_y - MAP_SIZE)))] \
				[count_x + (size *(int)(x - (p->pos_x - MAP_SIZE)))] = 0xFF00FF;	
			else if (p->cpy_map[y][x] == 'I')
				p->buf[count_y + (size * (int)(y - (p->pos_y - MAP_SIZE)))] \
				[count_x + (size * (int)(x - (p->pos_x - MAP_SIZE)))] = 0xFFFFFF;
			else if (p->cpy_map[y][x] == '.')
				p->buf[count_y + (size * (int)(y - (p->pos_y - MAP_SIZE)))] \
				[count_x + (size * (int)(x - (p->pos_x - MAP_SIZE)))] = 0xFF0000;	
		}
	}
}

void	minimap(t_player *p)
{
	int	y;
	int	x;

	y = p->pos_y - MAP_SIZE;
	while (y <= p->pos_y + MAP_SIZE)
	{
		x = p->pos_x - MAP_SIZE;
		while (x <= p->pos_x + MAP_SIZE)
			fill_buff_minimap(p, y, x++);
		y++;
	}
}

int	ray_cast(t_player *player)
{
	t_dda	dda;
	int		y;
	int		x;

	y = 0;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			if (y >= HEIGHT / 2)
				player->buf[y][x] = player->floor;
			else
				player->buf[y][x] = player->ceiling;
			x++;
		}
		y++;
	}
	dda.x = 0;
	while (dda.x < WIDTH)
		make_screen(player, &dda);
	minimap(player);
	draw(player);
	mlx_put_image_to_window(player->mlx, player->mlx_win, \
		player->img.img, 0, 0);
	return (0);
}
