/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jole <jole@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 07:50:51 by leklund           #+#    #+#             */
/*   Updated: 2023/05/26 15:17:40 by jole             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static void action_move(t_player *P, double y, double x)
{
	double	bodyX;
	double	bodyY;

	if(P->dirX < 0)

		bodyX = -BODY;
	else
		bodyX = BODY;
	if(P->dirY < 0)
		bodyY = -BODY;
	else
		bodyY = BODY;
	 //printf("Player is at Y[%f], X[%f]\n", P->playerY, P->playerX);
	 //printf("Player [Y] wanna move to Y[%f], X[%f]\n", bodyY + P->playerY + y, bodyX + P->playerX);
	 //printf("Player [X] wanna move to Y[%f], X[%f]\n", bodyY + P->playerY + y, bodyX + P->playerX + x);

	if(P->map[(int)(bodyY + P->playerY + y)][(int)(bodyX + P->playerX)] == '.'
			&& P->map[(int)(P->playerY + y)][(int)(P->playerX)] == '.')
		P->playerY += y;
	if(P->map[(int)(bodyY + P->playerY)][(int)(bodyX + P->playerX + x)] == '.'
			&& P->map[(int)(P->playerY)][(int)(P->playerX + x)] == '.')
		P->playerX += x;
	// printf("Player is at Y[%f], X[%f]\n", P->playerY, P->playerX);
}
void player_move(t_player *P, double x, double y, int type)
{
	if(type == KEY_W || type == KEY_S)
		action_move(P, P->dirY * y, P->dirX * x);
	else
	{
		action_move(P, -P->dirX * y, P->dirY * x);
	}
	ray_cast(P);
	mlx_put_image_to_window(P->mlx, P->mlx_win, P->reset_img, 0, 0);
	mlx_put_image_to_window(P->mlx, P->mlx_win, P->img, 0, 0);
}

void player_rotate(t_player *P, double x)
{
	double oldDirX = P->dirX;
	P->dirX =  P->dirX * cos(x) - P->dirY * sin(x);
	P->dirY = oldDirX * sin(x) + P->dirY * cos(x);
	double oldPlaneX = P->planeX;
	P->planeX = P->planeX * cos(x) - P->planeY * sin(x);
	P->planeY = oldPlaneX * sin(x) + P->planeY * cos(x);
	ray_cast(P);
	mlx_put_image_to_window(P->mlx, P->mlx_win, P->reset_img, 0, 0);
	mlx_put_image_to_window(P->mlx, P->mlx_win, P->img, 0, 0);
}



