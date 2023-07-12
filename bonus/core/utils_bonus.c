/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leklund <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 15:07:53 by leklund           #+#    #+#             */
/*   Updated: 2023/06/15 15:07:54 by leklund          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D_bonus.h"

int	create_trgb_arr(int arr[4])
{
	return (0 << 24 | arr[0] << 16 | arr[1] << 8 | arr[3]);
}

void	actually_draw_gun(t_player *P)
{
	int	x;
	int	y;
	int	color;

	y = 0;
	while (y < GUN_HEIGHT)
	{
		x = 0;
		while (x < GUN_WIDTH)
		{
			color = (int)P->gun[P->gun_index][GUN_HEIGHT * y + x];
			if ((unsigned int)color != 0xFF000000)
				P->buf[HEIGHT - GUN_HEIGHT + y][WIDTH / 2 - 70 + x] = color;
			x++;
		}
		y++;
	}
}

void	draw_gun(t_player *player)
{
	if (player->shoot)
	{
		player->shoot -= player->d_time;
		if (player->shoot <= 0)
		{
			if (player->gun_index >= 4)
			{
				player->gun_index = 0;
				player->shoot = 0;
			}
			else
			{
				player->gun_index++;
				player->shoot = 0.05;
			}
		}
	}
	actually_draw_gun(player);
}

void	get_time(t_player *player)
{
	struct timeval	t;
	double			elapsed;

	gettimeofday(&t, NULL);
	elapsed = (t.tv_sec - player->time.tv_sec) * 1000;
	elapsed += (t.tv_usec - player->time.tv_usec) / 1000;
	player->d_time = elapsed / 1000;
	player->time = t;
}
