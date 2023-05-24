/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_handle.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leklund <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 07:50:20 by leklund           #+#    #+#             */
/*   Updated: 2023/05/24 07:50:23 by leklund          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "cub3d.h"

int	key_pressed(int keycode, void *param)
{
	if (keycode == 13)
		player_move1(param, 0.1, 0.1);
	else if (keycode == 1)
		player_move1(param, -0.1, -0.1);
	else if (keycode == 0)
		player_move2(param, -0.1, -0.1);
	else if (keycode == 2)
		player_move2(param, 0.1, 0.1);
	else if (keycode == 124)
		player_rotate(param, -0.1);
	else if (keycode == 123)
		player_rotate(param, 0.1);
	return (0);
}

int	red_cross_close(void)
{
	exit(0);
}
