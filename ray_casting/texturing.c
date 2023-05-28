/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texturing.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jole <jole@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 07:36:31 by leklund           #+#    #+#             */
/*   Updated: 2023/05/26 15:15:53 by jole             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	draw(t_player *P)
{
	for (int y = 0; y < screenHeight; y++)
	{
		for (int x = 0; x < screenWidth; x++)
		{
			P->img.data[y * screenWidth + x] = P->buf[y][x];
		}
	}
	// mlx_put_image_to_window(P->mlx, P->mlx_win, P->img.img, 0, 0);
}

int	choose_texture(t_player *P, t_dda *dda)
{
	int	tex_num;
	(void) P;
	if (dda->side == 1)
	{
		if (dda->rayDirY <= 0)
			tex_num = 0;
		else
			tex_num = 1;
	}
	else
	{
		if (dda->rayDirX <= 0)
			tex_num = 2;
		else
			tex_num = 3;
	}
	return (tex_num);
}

void	texture(t_player *P, t_dda *dda)
{
	int texNum = choose_texture(P, dda);
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
	double texPos = (dda->drawStart - screenHeight / 2 + dda->lineHeight / 2) * step;
	int y = dda->drawStart;
	while(y < dda->drawEnd)
	{
		// Cast the texture coordinate to integer, and mask with (texHeight - 1) in case of overflow
		int texY = (int)texPos & (texHeight - 1);
		texPos += step;

		int	color = P->texture[texNum][texHeight * texY + texX];
		// if(dda->side == 1)
		// 	color = (color >> 1) & 8355711;
		P->buf[y][dda->x] = color;
		y++;
	}

}