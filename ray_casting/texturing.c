/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texturing.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leklund <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 07:36:31 by leklund           #+#    #+#             */
/*   Updated: 2023/05/25 07:36:32 by leklund          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "cub3D.h"


// static int	create_trgb(int t, int r, int g, int b)
// {
// 	return (t << 24 | r << 16 | g << 8 | b);
// }

static void	my_mlx_pixel_put(t_player *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

void	ver_line(t_player *P, t_dda *dda, int color)
{
	// while (dda->drawStart < dda->drawEnd)
	// while (dda->drawStart < dda->drawStart+1)
	while (dda->drawStart < dda->drawEnd)
	{
		my_mlx_pixel_put(P, dda->x, dda->drawStart, color);
		dda->drawStart++;
	}
}


void	texture(t_player *P, t_dda *dda)
{
	if (P->texture[0] == NULL)
		printf("SHIT\n");
	// unsigned int buffer[screenHeight][screenWidth];
	// int texNum = P->map[dda->mapY][dda->mapX] - 1; //1 subtracted from it so that texture 0 can be used!
	double wallX; //where exactly the wall was hit
	if (dda->side == 0)
		wallX = P->playerY + dda->perpWallDist * dda->rayDirY;
	else
		wallX = P->playerX + dda->perpWallDist * dda->rayDirX;
	wallX -= floor((wallX));
	 //x coordinate on the texture
	int texX = (int)(wallX * (double)(texWidth));
	if(dda->side == 0 && dda->rayDirX > 0)
		texX = texWidth - texX - 1;
	if(dda->side == 1 && dda->rayDirY < 0)
		texX = texWidth - texX - 1;
	// How much to increase the texture coordinate per screen pixel
	double step = 1.0 * texHeight / dda->lineHeight;
	// Starting texture coordinate
	// printf("%i - (%i/2) + (%i/2)\n", dda->drawStart, screenHeight, dda->lineHeight);
	double texPos = (dda->drawStart - screenHeight / 2 + dda->lineHeight / 2) * step;
	// printf("texPos[%i]\n", texX);
	// (void) buffer;
	// (void) texPos;
	// (void) texNum;
	int y = dda->drawStart;
	// printf("x[%i] startdraw[%i], drawEnd[%i]\n", dda->x, y, dda->drawEnd);
	// P->addr = mlx_get_data_addr(P->texture[0], &P->bits_per_pixel, &P->line_length,
	// 									&P->endian);
	while(y < dda->drawEnd)
	{
		// Cast the texture coordinate to integer, and mask with (texHeight - 1) in case of overflow
		int texY = (int)texPos & (texHeight - 1);
	// (void) texY;
		
		// printf("Y[%i], X[%i]\n", y, dda->x);
		// texPos += step;
		unsigned int *image_pixels = (unsigned int*)P->texture[0];
		// unsigned int *image_pixels = (unsigned int*)P->addr;
		// if (y%10 == 0)
		// 	printf("X[%i], texX[%i], texY[%i]\n", dda->x, texX, texY);

		unsigned int color = image_pixels[texHeight * texY + texX];
		// printf("Size[%lu] num[%d], Color[%x]\n", sizeof(P->addr), texHeight * texY + texX, color);
		// unsigned int color = image_pixels[texHeight * texY + texX];
		// (void) color;
		// printf("hi1\n");
		// put_pixel(&P->img, cub3d->ray.index, *i, color);
		// Uint32 color = texture[texNum][texHeight * texY + texX];
		// //make color darker for y-sides: R, G and B byte each divided through two with a "shift" and an "and"
		// if(dda->side == 1) color = (color >> 1) & 8355711;
		// buffer[y][dda->x] = color;
		my_mlx_pixel_put(P, dda->x, y, color);
		// ver_line(P, dda, color);
		y++;
	}

}

// void	texture1(t_player *P, t_dda *dda)
// {
// 	unsigned int buffer[screenHeight][screenWidth];

// 	//texturing calculations
// 	int texNum = P->map[dda->mapX][dda->mapY] - 1; //1 subtracted from it so that texture 0 can be used!

// 	//calculate value of wallX
// 	double wallX; //where exactly the wall was hit
// 	if (dda->side == 0) wallX = P->playerY + dda->perpWallDist * dda->rayDirY;
// 	else           wallX = P->playerX + dda->perpWallDist * dda->rayDirX;
// 	wallX -= floor((wallX));

// 	//x coordinate on the texture
// 	int texX = (int)(wallX * (double)(texWidth));
// 	if(dda->side == 0 && dda->rayDirX > 0) texX = texWidth - texX - 1;
// 	if(dda->side == 1 && dda->rayDirY < 0) texX = texWidth - texX - 1;

// 	// How much to increase the texture coordinate per screen pixel
// 	double step = 1.0 * texHeight / dda->lineHeight;
// 	// Starting texture coordinate
// 	double texPos = (dda->drawStart - screenHeight / 2 + dda->lineHeight / 2) * step;
// 	for(int y = dda->drawStart; y < dda->drawEnd; y++)
// 	{
// 		// Cast the texture coordinate to integer, and mask with (texHeight - 1) in case of overflow
// 		int texY = (int)texPos & (texHeight - 1);
// 		texPos += step;
// 		unsigned int *image_pixels = (unsigned int*)P->texture[texNum];
// 		unsigned int color = image_pixels[texHeight * texY + texX];
// 		// Uint32 color = texture[texNum][texHeight * texY + texX];
// 		//make color darker for y-sides: R, G and B byte each divided through two with a "shift" and an "and"
// 		if(dda->side == 1) color = (color >> 1) & 8355711;
// 		buffer[y][dda->x] = color;
// 	}
// }