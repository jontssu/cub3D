/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leklund <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/04 07:33:54 by leklund           #+#    #+#             */
/*   Updated: 2023/06/04 07:33:56 by leklund          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D_bonus.h"

int mouse_rotate(int x, int y, t_player *player)
{
	// printf("%d, %d\n", x, y);
	if (x < 0 || x > WIDTH || y < 0 || y > HEIGHT)
	{
		player->rotate_right = 0;
		player->rotate_left = 0;
		return (-1);
	}
	if (x > player->prev_rot_x)
		player->rotate_right = ROT_SPEED * ((double)(x - player->prev_rot_x) / 3.5);
	else if (x < player->prev_rot_x)
		player->rotate_left = -ROT_SPEED * ((double)(player->prev_rot_x - x) / 3.5);
	else
	{
		player->rotate_right = 0;
		player->rotate_left = 0;
	}
	// if (x > player->prev_rot_x)
	// 	player_rotate(player, ROT_SPEED * (x - player->prev_rot_x));
	// else if (x < player->prev_rot_x)
	// 	player_rotate(player, -ROT_SPEED * (player->prev_rot_x - x));
	player->prev_rot_x = x;
	(void) y;
	return (0);
}
