/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jole <jole@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 07:50:51 by leklund           #+#    #+#             */
/*   Updated: 2023/05/31 12:16:56 by jole             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static void	action_move(t_player *P, double y, double x)
{
	double	body_x;
	double	body_y;

	if (P->dir_x < 0)

		body_x = -BODY;
	else
		body_x = BODY;
	if (P->dir_y < 0)
		body_y = -BODY;
	else
		body_y = BODY;
	if (P->map[(int)(body_y + P->pos_y + y)][(int)(body_x + P->pos_x)] == '.'
			&& P->map[(int)(P->pos_y + y)][(int)(P->pos_x)] == '.')
		P->pos_y += y;
	if (P->map[(int)(body_y + P->pos_y)][(int)(body_x + P->pos_x + x)] == '.'
			&& P->map[(int)(P->pos_y)][(int)(P->pos_x + x)] == '.')
		P->pos_x += x;
}

void	player_move(t_player *P, double x, double y, int type)
{
	if (type == KEY_W || type == KEY_S)
		action_move(P, P->dir_y * y, P->dir_x * x);
	else
	{
		action_move(P, -P->dir_x * y, P->dir_y * x);
	}
	ray_cast(P);
	mlx_put_image_to_window(P->mlx, P->mlx_win, P->img.img, 0, 0);
}

void	player_rotate(t_player *P, double x)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = P->dir_x;
	old_plane_x = P->plane_x;
	P->dir_x = P->dir_x * cos(x) - P->dir_y * sin(x);
	P->dir_y = old_dir_x * sin(x) + P->dir_y * cos(x);
	P->plane_x = P->plane_x * cos(x) - P->plane_y * sin(x);
	P->plane_y = old_plane_x * sin(x) + P->plane_y * cos(x);
	ray_cast(P);
	mlx_put_image_to_window(P->mlx, P->mlx_win, P->img.img, 0, 0);
}



