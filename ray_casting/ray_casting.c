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

static int	create_trgb(int t, int r, int g, int b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}

static void	my_mlx_pixel_put(t_player *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

void	ver_line1(t_player *P, t_dda *dda, int color)
{
	int	color2 = create_trgb (255,255,255,255);
	int	y;

	y = 0;
	while (y < screenHeight) // tmp black image remove!<---------- REMOVE!!!!!!!!!!
	{
		my_mlx_pixel_put(P, dda->x, y, color2);
		y++;
	}
	y = dda->drawStart;
	while (dda->drawStart < dda->drawEnd)
	{
		my_mlx_pixel_put(P, dda->x, dda->drawStart, color);
		dda->drawStart++;
	}
	dda->drawStart = y;
}

void	draw_ver_line(t_player *P, t_dda *dda)
{
	int	color;
	(void) P;
	color = create_trgb(0,0,255,0);
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
	ver_line1(P, dda, color);
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
		if (P->map[dda->mapY][dda->mapX] > '.')
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
	// while (dda.x < screenWidth)
	// while (dda.x < 10)
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
		// printf("drawStart[%i] - h[%i] + lineHeight[%i]\n", dda.drawStart, screenHeight, dda.lineHeight);
		// texture(P, &dda);
		dda.hit = 0;
		dda.x++;
	}
	print_map(P);
	free(P->cpy_map);
	P->cpy_map = copy2DCharArray(P->map);
	return (0);
}
