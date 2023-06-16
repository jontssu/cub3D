/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_casting_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jole <jole@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 16:29:50 by jole              #+#    #+#             */
/*   Updated: 2023/06/14 17:24:10 by jole             ###   ########.fr       */
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
		if (!dda->hit)
			P->cpy_map[dda->map_y][dda->map_x] = '/';
		if (P->map[dda->map_y][dda->map_x] == 'O')
			P->cpy_map[dda->map_y][dda->map_x] = 'O';
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
	return (0);
}
