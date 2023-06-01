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

#include "cub3d.h"

int	key_pressed(int keycode, t_player *param)
{
	if (keycode == KEY_W)
		param->move_w = keycode;
	if (keycode == KEY_S)
		param->move_s = keycode;
	if (keycode == KEY_A)
		param->move_a = keycode;
	if (keycode == KEY_D)
		param->move_d = keycode;
	if (keycode == KEY_ESC)
		free_all(param);
	else if (keycode == KEY_LEFT)
		param->rotate = ROT_SPEED;
	else if (keycode == KEY_RIGHT)
		param->rotate = -ROT_SPEED;
	return (0);
}
int	key_release(int keycode, t_player *param)
{
	if (keycode == KEY_W)
		param->move_w = -1;
	if (keycode == KEY_S)
		param->move_s = -1;
	if (keycode == KEY_A)
		param->move_a = -1;
	if (keycode == KEY_D)
		param->move_d = -1;
	else if (keycode == KEY_LEFT || keycode == KEY_RIGHT)
		param->rotate = 0;
	return (0);
}

int	free_all(t_player *param)
{
	mlx_destroy_window(param->mlx, param->mlx_win);
	free_elements(param->elements);
	exit(0);
	return (0);
}