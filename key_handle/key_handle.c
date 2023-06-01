/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_handle.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jole <jole@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 07:50:20 by leklund           #+#    #+#             */
/*   Updated: 2023/05/31 18:12:56 by jole             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	key_pressed(int keycode, void *param)
{
	if (keycode == KEY_W)
		player_move(param, SPEED, SPEED, KEY_W);
	else if (keycode == KEY_S)
		player_move(param, -SPEED, -SPEED, KEY_S);
	else if (keycode == KEY_D)
		player_move(param, -SPEED, -SPEED, KEY_A);
	else if (keycode == KEY_A)
		player_move(param, SPEED, SPEED, KEY_D);
	else if (keycode == KEY_LEFT)
		player_rotate(param, ROT_SPEED);
	else if (keycode == KEY_RIGHT)
		player_rotate(param, -ROT_SPEED);
	else if (keycode == KEY_ESC)
		free_all(param);
	return (0);
}

int	key_release(int keycode, void *param)
{

}

int	free_all(t_player *param)
{
	mlx_destroy_window(param->mlx, param->mlx_win);
	free_elements(param->elements);
	exit(0);
	return (0);
}