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

#include "cub3d.h"

static void	action_move(t_player *player, double y, double x)
{
	if (player->map[(int)(player->pos_y + y)][(int)(player->pos_x)] == '.')
		player->pos_y += y;
	if (player->map[(int)(player->pos_y)][(int)(player->pos_x + x)] == '.')
		player->pos_x += x;
}

void	player_move(t_player *player)
{
	if (player->move_w == KEY_W)
		action_move(player, player->dir_y * SPEED, player->dir_x * SPEED);
	if (player->move_s == KEY_S)
		action_move(player, player->dir_y * -SPEED, player->dir_x * -SPEED);
	if (player->move_a == KEY_A)
 		action_move(player, -player->dir_x * SPEED, player->dir_y * SPEED);
	if (player->move_d == KEY_D)
 		action_move(player, -player->dir_x * -SPEED, player->dir_y * -SPEED);
}

void	player_rotate(t_player *P, double x)
{
	double	old_dir_x;
	double	old_plane_x;

	if (!x)
		return;
	old_dir_x = P->dir_x;
	old_plane_x = P->plane_x;
	P->dir_x = P->dir_x * cos(x) - P->dir_y * sin(x);
	P->dir_y = old_dir_x * sin(x) + P->dir_y * cos(x);
	P->plane_x = P->plane_x * cos(x) - P->plane_y * sin(x);
	P->plane_y = old_plane_x * sin(x) + P->plane_y * cos(x);
	ray_cast(P);
	// mlx_put_image_to_window(P->mlx, P->mlx_win, P->img.img, 0, 0);
}



