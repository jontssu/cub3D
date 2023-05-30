/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_handle.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jole <jole@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 07:50:20 by leklund           #+#    #+#             */
/*   Updated: 2023/05/29 16:14:29 by jole             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	key_pressed(int keycode, void *param)
{
	if (keycode == KEY_W)
		player_move(param, 0.1, 0.1, KEY_W);
	else if (keycode == KEY_S)
		player_move(param, -0.1, -0.1, KEY_S);
	else if (keycode == KEY_A)
		player_move(param, -0.1, -0.1, KEY_A);
	else if (keycode == KEY_D)
		player_move(param, 0.1, 0.1, KEY_D);
	else if (keycode == KEY_LEFT)
		player_rotate(param, -0.1);
	else if (keycode == KEY_RIGHT)
		player_rotate(param, 0.1);
	else if (keycode == KEY_ESC)
		esc_close_window();
	return (0);
}

int	red_cross_close(void)
{
	//should free stuff
	exit(0);
}

int	esc_close_window(void)
{
	//should free stuff
	exit (0);
}