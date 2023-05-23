/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_casting.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leklund <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 05:51:03 by leklund           #+#    #+#             */
/*   Updated: 2023/05/19 05:51:05 by leklund          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "cub3d.h"

int	create_trgb(int t, int r, int g, int b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}

void	my_mlx_pixel_put(t_player *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

void verLine(t_player *P, int x, int drawStart, int drawEnd, int color)
{
	int color2 = create_trgb (255,255,255,255);
	int y = 0;
	while (y < P->ResY) // tmp black image remove!<---------- REMOVE!!!!!!!!!!
	{
		my_mlx_pixel_put(P, x, y, color2);
		y++;
	}
	while (drawStart < drawEnd)
	{
		my_mlx_pixel_put(P, x, drawStart, color);
		drawStart++;
	}
}

void drawVerLine(t_player *P, t_dda *dda)
{
	int color;

	color = create_trgb(0,0,255,0);
	//Calculate distance projected on camera direction removing fisheye effect!
		if(dda->side == 0)
		{
			dda->perpWallDist = (dda->sideDistX - dda->deltaDistX);
		}
		else
		{
			dda->perpWallDist = (dda->sideDistY - dda->deltaDistY);
		}
		//Calculate height of line to draw on screen
		dda->lineHeight = (int)(P->ResY / dda->perpWallDist);
		
		dda->drawStart = -dda->lineHeight / 2 + P->ResY / 2;

		//calculate lowest and highest pixel to fill in current stripe
		if(dda->drawStart < 0)
			dda->drawStart = 0;
		dda->drawEnd = dda->lineHeight / 2 + P->ResY / 2;
		if(dda->drawEnd >= P->ResY)
			dda->drawEnd = P->ResY - 1;
		//draw the pixels of the stripe as a vertical line
		verLine(P, dda->x, dda->drawStart, dda->drawEnd, color);
}

void	Digital_Differential_Analysis(t_player *P, t_dda *dda)
{
	//perform DDA (Digital Differential Analysis)
	while (dda->hit == 0)
	{

		//jump to next map square, either in x-direction, or in y-direction
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
		//Check if ray has hit a wall
		P->cpy_map[dda->mapY][dda->mapX] = '/';
		if (P->map[dda->mapY][dda->mapX] > '0')
			dda->hit = 1;
	} 
}

void start_Dir_Len(t_player *P, t_dda *dda)
{
	//calculate step and initial sideDist
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
	t_dda dda;

	dda.x = 0;
	while(dda.x < P->ResX)
	{
		//init starting values
		dda.hit = 0;
		dda.mapX = (int)P->playerX; //current cords vector is in.
		dda.mapY = (int)P->playerY;
		dda.cameraX = 2 * dda.x / (double)P->ResX - 1; //generates values between -1 to 1 depndig if x is more left or right of the view
		dda.rayDirX = P->dirX + (P->planeX * dda.cameraX);//the angle where the ray will be cast to from the player.
      	dda.rayDirY = P->dirY + (P->planeY * dda.cameraX);
		dda.deltaDistX = (dda.rayDirX == 0) ? 1e30 : fabs(1.0 / dda.rayDirX); 
		dda.deltaDistY = (dda.rayDirY == 0) ? 1e30 : fabs(1.0 / dda.rayDirY);
		start_Dir_Len(P, &dda);
		Digital_Differential_Analysis(P, &dda);
		drawVerLine(P, &dda);
		dda.hit = 0;
		dda.x++;
	}
	print_map(P);
	free(P->cpy_map);
	P->cpy_map = copy2DCharArray(P->map);
	return (0);
}
