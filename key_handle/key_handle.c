/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_handle.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jole <jole@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 07:50:20 by leklund           #+#    #+#             */
/*   Updated: 2023/06/01 18:48:41 by jole             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	key_pressed(int keycode, t_player *param)
{
	if (keycode == KEY_W)
		param->move_w = 1;
	else if (keycode == KEY_S)
		param->move_s = 1;
	else if (keycode == KEY_A)
		param->move_a = 1;
	else if (keycode == KEY_D)
		param->move_d = 1;
	else if (keycode == KEY_LEFT)
		param->rotate_left = ROT_SPEED;
	else if (keycode == KEY_RIGHT)
		param->rotate_right = -ROT_SPEED;
	else if (keycode == KEY_ESC)
		free_all(param);
	return (0);
}

int	key_release(int keycode, t_player *param)
{
	if (keycode == KEY_W)
		param->move_w = 0;
	else if (keycode == KEY_S)
		param->move_s = 0;
	else if (keycode == KEY_A)
		param->move_a = 0;
	else if (keycode == KEY_D)
		param->move_d = 0;
	else if (keycode == KEY_LEFT)
		param->rotate_left = 0;
	else if (keycode == KEY_RIGHT)
		param->rotate_right = 0;
	return (0);
}

int	free_all(t_player *param)
{
	if (param->mlx && param->mlx_win)
		mlx_destroy_window(param->mlx, param->mlx_win);
	free_elements(param->elements);
	exit(0);
	return (0);
}
