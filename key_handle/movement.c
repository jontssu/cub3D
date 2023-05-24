/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leklund <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 07:50:51 by leklund           #+#    #+#             */
/*   Updated: 2023/05/24 07:50:52 by leklund          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "cub3d.h"

void player_move1(t_player *P, double x, double y)
{
	if(P->map[(int)(P->playerY + P->dirY * y)][(int)P->playerX] == '0')
		P->playerY += P->dirY * y;
	if(P->map[(int)(P->playerY)][(int)(P->playerX + P->dirX * x)] == '0')
		P->playerX += P->dirX * x;
	ray_cast(P);
	mlx_put_image_to_window(P->mlx, P->mlx_win, P->reset_img, 0, 0);
	mlx_put_image_to_window(P->mlx, P->mlx_win, P->img, 0, 0);
}

void player_move2(t_player *P, double x, double y)
{
	if(P->map[(int)(P->playerY + -P->dirX * y)][(int)P->playerX] == '0')
		P->playerY += -P->dirX * y;
	if(P->map[(int)(P->playerY)][(int)(P->playerX + P->dirY * x)] == '0')
		P->playerX += P->dirY * x;
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



