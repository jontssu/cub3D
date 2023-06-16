/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jole <jole@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/04 06:32:04 by leklund           #+#    #+#             */
/*   Updated: 2023/06/14 17:25:41 by jole             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D_bonus.h"

double	body_move(double dir_1, double dir_2, int key, int reverse)
{
	if (dir_1 < 0 && key == KEY_W)
		return (-BODY);
	else if (dir_1 >= 0 && key == KEY_W)
		return (BODY);
	else if (dir_1 < 0 && key == KEY_S)
		return (BODY);
	else if (dir_1 >= 0 && key == KEY_S)
		return (-BODY);
	else if (dir_2 < 0 && key == KEY_A)
		return (-BODY * reverse);
	else if (dir_2 >= 0 && key == KEY_A)
		return (BODY * reverse);
	else if (dir_2 < 0 && key == KEY_D)
		return (BODY * reverse);
	else if (dir_2 >= 0 && key == KEY_D)
		return (-BODY * reverse);
	return (BODY);
}

static void	action_move(t_player *player, double y, double x, int key)
{
	double	bod_x;
	double	bod_y;
	double	pos_y;
	double	pos_x;

	pos_y = player->pos_y;
	pos_x = player->pos_x;
	bod_x = body_move(player->dir_x, player->dir_y, key, 1);
	bod_y = body_move(player->dir_y, player->dir_x, key, -1);
	if ((player->map[(int)(pos_y + y + bod_y)][(int)(pos_x + bod_x)] == '.' &&
		(player->map[(int)(pos_y + y + bod_y)][(int)(pos_x - bod_x)] == '.' ||
		player->map[(int)(pos_y + y + bod_y)][(int)(pos_x - bod_x)] == 'O')) ||
		(player->map[(int)(pos_y + y + bod_y)][(int)(pos_x + bod_x)] == 'O' &&
		(player->map[(int)(pos_y + y + bod_y)][(int)(pos_x - bod_x)] == 'O' ||
		player->map[(int)(pos_y + y + bod_y)][(int)(pos_x - bod_x)] == '.')))
		player->pos_y += y;
	pos_y = player->pos_y;
	if ((player->map[(int)(pos_y + bod_y)][(int)(pos_x + x + bod_x)] == '.' &&
		(player->map[(int)(pos_y - bod_y)][(int)(pos_x + x + bod_x)] == '.' ||
		player->map[(int)(pos_y - bod_y)][(int)(pos_x + x + bod_x)] == 'O')) ||
		(player->map[(int)(pos_y + bod_y)][(int)(pos_x + x + bod_x)] == 'O' &&
		(player->map[(int)(pos_y - bod_y)][(int)(pos_x + x + bod_x)] == 'O' ||
		player->map[(int)(pos_y - bod_y)][(int)(pos_x + x + bod_x)] == '.')))
		player->pos_x += x;
}

void	player_move(t_player *player)
{
	if (player->move_w)
		action_move(player, player->dir_y * SPEED, \
		player->dir_x * SPEED, KEY_W);
	if (player->move_s)
		action_move(player, player->dir_y * -SPEED, \
		player->dir_x * -SPEED, KEY_S);
	if (player->move_a)
		action_move(player, -player->dir_x * SPEED, \
		player->dir_y * SPEED, KEY_A);
	if (player->move_d)
		action_move(player, -player->dir_x * -SPEED, \
		player->dir_y * -SPEED, KEY_D);
}

void	player_rotate(t_player *P, double x)
{
	double	old_dir_x;
	double	old_plane_x;

	if (!x)
		return ;
	old_dir_x = P->dir_x;
	old_plane_x = P->plane_x;
	P->dir_x = P->dir_x * cos(x) - P->dir_y * sin(x);
	P->dir_y = old_dir_x * sin(x) + P->dir_y * cos(x);
	P->plane_x = P->plane_x * cos(x) - P->plane_y * sin(x);
	P->plane_y = old_plane_x * sin(x) + P->plane_y * cos(x);
}
