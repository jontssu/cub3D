/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_casting.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jole <jole@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 05:51:03 by leklund           #+#    #+#             */
/*   Updated: 2023/05/26 15:18:00 by jole             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"
#include "parsing.h"

void	draw_ver_line(t_player *P, t_dda *dda)
{
	(void) P;
	if (dda->side == 0)
	{
		dda->perpWallDist = (dda->sideDistX - dda->deltaDistX);
	}
	else
	{
		dda->perpWallDist = (dda->sideDistY - dda->deltaDistY);
	}
	dda->lineHeight = (int)(screenHeight / dda->perpWallDist);
	dda->drawStart = -dda->lineHeight / 2 + screenHeight / 2;
	if (dda->drawStart < 0)
		dda->drawStart = 0;
	dda->drawEnd = dda->lineHeight / 2 + screenHeight / 2;
	if (dda->drawEnd >= screenHeight)
		dda->drawEnd = screenHeight - 1;
}

void	digital_differential_analysis(t_player *P, t_dda *dda)
{
	while (dda->hit == 0)
	{
		if (dda->sideDistX < dda->sideDistY)
		{
			dda->sideDistX += dda->deltaDistX;
			dda->mapX += dda->stepX;
			dda->side = 0;
		}
		else
		{
			dda->sideDistY += dda->deltaDistY;
			dda->mapY += dda->stepY;
			dda->side = 1;
		}
		P->cpy_map[dda->mapY][dda->mapX] = '/';
		if (P->map[dda->mapY][dda->mapX] == 'I')
			dda->hit = 1;
	}
}

void	start_dir_len(t_player *P, t_dda *dda)
{
	if (dda->rayDirX < 0)
	{
		dda->stepX = -1;
		dda->sideDistX = (P->playerX - dda->mapX) * dda->deltaDistX;
	}
	else
	{
		dda->stepX = 1;
		dda->sideDistX = (dda->mapX + 1.0 - P->playerX) * dda->deltaDistX;
	}
	if (dda->rayDirY < 0)
	{
		dda->stepY = -1;
		dda->sideDistY = (P->playerY - dda->mapY) * dda->deltaDistY;
	}
	else
	{
		dda->stepY = 1;
		dda->sideDistY = (dda->mapY + 1.0 - P->playerY) * dda->deltaDistY;
	}
}

int	ray_cast(t_player *P)
{
	t_dda	dda;

	
	dda.x = 0;

	// ft_bzero(P->buf, screenWidth * screenHeight * sizeof(int));

	for (int i = 0; i < screenHeight; i++)
	{
		for (int j = 0; j < screenWidth; j++)
		{
			if (i >= screenHeight/2)
				P->buf[i][j] = P->floor;
			else
				P->buf[i][j] = P->ceiling;
		}
	}

	while (dda.x < screenWidth)
	{
		dda.hit = 0;
		dda.mapX = (int)P->playerX;
		dda.mapY = (int)P->playerY;
		dda.cameraX = 2 * dda.x / (double)screenWidth - 1;
		dda.rayDirX = P->dirX + (P->planeX * dda.cameraX);
		dda.rayDirY = P->dirY + (P->planeY * dda.cameraX);
		dda.deltaDistX = (dda.rayDirX == 0) ? 1e30 : fabs(1.0 / dda.rayDirX); 
		dda.deltaDistY = (dda.rayDirY == 0) ? 1e30 : fabs(1.0 / dda.rayDirY);
		start_dir_len(P, &dda);
		digital_differential_analysis(P, &dda);
		draw_ver_line(P, &dda);
		texture(P, &dda);
		dda.hit = 0;
		dda.x++;
	}
	print_map(P);
	free_double_pointer(P->cpy_map);
	P->cpy_map = copy2DCharArray(P->map);
	draw(P);

	return (0);
}
