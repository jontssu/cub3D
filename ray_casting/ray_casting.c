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
	// (void) drawStart;
	// printf("BEGIN:startY:%i, endY:%i. ", drawEnd, drawEnd);
	while (drawStart < drawEnd)
	{
		// printf("startY:%i, endY:%i. ", drawStart, drawEnd);
		my_mlx_pixel_put(P, x, drawStart, color);
		drawStart++;
	}

}


int	ray_cast(t_player *P)
{
	int	x;
	double cameraX; //cam x pos
	double rayDirX; // direction to work with the ray/vector from player to make FOV
	double rayDirY;
	double deltaDistX;//the amount to increase measure vector
	double deltaDistY;
	double sideDistX;//mesaure vector total
	double sideDistY;
	double perpWallDist; //the length from POV to wall
	int stepX; //what direction to step into x or y
	int stepY;
	int hit; //was there a wall hit?
	int side; //was a NS or a EW wall hit?
	int mapX; //current vector hit pos
	int mapY;



	//Calculate height of line to draw on screen
	int h = P->ResY;
	int lineHeight;
	//calculate lowest and highest pixel to fill in current stripe
    int drawStart;
    int drawEnd;
	printf("x: %f, y: %f\n", P->playerX, P->playerY);

	int color;
	x = 0;
	while(x < P->ResX)
	{
		hit = 0;
		mapX = (int)P->playerX; //current cords vector is in.
		mapY = (int)P->playerY;
		cameraX = 2 * x / (double)P->ResX - 1; //generates values between -1 to 1 depndig if x is more left or right of the view
		rayDirX = P->dirX + P->planeX * cameraX;//the angle where the ray will be cast to from the player.
      	rayDirY = P->dirY + P->planeY * cameraX;
		
		// printf("%i= %d\n",mapX, mapY);
		deltaDistX = (rayDirX == 0) ? 1e30 : fabs(1.0 / rayDirX); //
		deltaDistY = (rayDirY == 0) ? 1e30 : fabs(1.0 / rayDirY);
		// printf("deltaDistX[%f], deltaDistY[%f]\n", deltaDistX, deltaDistY);
		// printf("\nX[%i]: cameraX:[%f]\n rayDirX:[%f], deltaDistX[%f] rayDirY:[%f], deltaDistY[%f]\n",x, cameraX, rayDirX, deltaDistX, rayDirY, deltaDistY);

		// printf("%i*%i = %d\n",2,x,2*x);

		//calculate step and initial sideDist
		if (rayDirX < 0)
		{
			// printf("A\n");
			stepX = -1;
			sideDistX = (P->playerX - mapX) * deltaDistX;
		}
		else
		{
			// printf("B\n");
			stepX = 1;
			sideDistX = (mapX + 1.0 - P->playerX) * deltaDistX;
		}
		if (rayDirY < 0)
		{
			// printf("C\n");
			stepY = -1;
			sideDistY = (P->playerY - mapY) * deltaDistY;
		}
		else
		{
			// printf("D\n");
			stepY = 1;
			sideDistY = (mapY + 1.0 - P->playerY) * deltaDistY;
		}
		// printf("stepX[%i], sideDistX[%f], deltaDistX[%f], stepY[%i], sideDistY[%f], deltaDistY[%f]\n",stepX, sideDistX, deltaDistX, stepY, sideDistY, deltaDistY);


		//perform DDA
		while (hit == 0)
		{
			// printf("type at: X[%i], Y[%i], is[%c]\n", mapX+1, mapY+1, P->map[mapX][mapY]);

			//jump to next map square, either in x-direction, or in y-direction
			if (sideDistX < sideDistY)
			{
			// printf("MovedX: sideDistX[%f] + deltaDistX[%f] = %f\n", sideDistX, deltaDistX, sideDistX + deltaDistX);
				sideDistX += deltaDistX;
				mapX += stepX;
				side = 0;
			}
			else
			{
				// printf("MovedY: sideDistY[%f] + deltaDistY[%f] = %f\n", sideDistY, deltaDistY, sideDistY + deltaDistY);
				sideDistY += deltaDistY;
				mapY += stepY;
				side = 1;
			}
			//Check if ray has hit a wall
			// printf("type at: X[%i], Y[%i], is[%c]\n", mapX, mapY, P->map[mapX][mapY]);

			if (P->map[mapX][mapY] > '0')
				hit = 1;
		} 
			// printf("type at: X[%i], Y[%i], is[%c]\n", mapX, mapY, P->map[mapX][mapY]);

		// printf("found wall at: X[%i], Y[%i]\n", mapX+1, mapY+1);

		//Calculate distance projected on camera direction removing fisheye effect!
		if(side == 0)
		{
			// printf("0 - X[%i]. ", x);
			// printf("sideDistX[%f] - deltaDistX[%f]. ", sideDistX, deltaDistX);
			perpWallDist = (sideDistX - deltaDistX);
			// printf("perpWallDist: %f\n", perpWallDist);
		}
		else
		{
			// printf("1 - X[%i]. ", x);
			// printf("sideDistY[%f] - deltaDistY[%f]. ", sideDistY, deltaDistY);
			perpWallDist = (sideDistY - deltaDistY);
			// printf("perpWallDist: %f\n", perpWallDist);
		}
		// if(perpWallDist == 0)
		// {
		// 	if(side == 0)
		// 		perpWallDist = deltaDistX;
		// 	else
		// 		perpWallDist = deltaDistY;

		// printf("X[%i], perpWallDist: %f\n", x, perpWallDist);
		// 	// x++;
		// 	// continue;
		// }

		//Calculate height of line to draw on screen
		lineHeight = (int)(h / perpWallDist);
		// printf("perpWallDist: %f\n", perpWallDist);
		
		// printf("lineHeight: %i = %d/%f. ", lineHeight, h, perpWallDist);
		drawStart = -lineHeight / 2 + h / 2;
		// printf("drawStart: %i = %d/2+%d/2.\n",drawStart, lineHeight, h);

		//calculate lowest and highest pixel to fill in current stripe
		if(drawStart < 0)
			drawStart = 0;
		drawEnd = lineHeight / 2 + h / 2;
		if(drawEnd >= h)
			drawEnd = h - 1;
		// printf("BEGIN:startY:%i, endY:%i\n", drawStart, drawEnd);
		color = create_trgb(0,0,255,0);
		//give x and y sides different brightness
      	// if(side == 1)
		// 	color = color / 2;
		//draw the pixels of the stripe as a vertical line
		verLine(P, x, drawStart, drawEnd, color);
		hit = 0;
		x++;
		// printf("pass\n");
	}
		// printf("pass GOOD\n");

	// exit(0);
	//     for(int x = 0; x < w; x++)
    // {
    //   //calculate ray position and direction
    //   double cameraX = 2 * x / double(w) - 1; //x-coordinate in camera space
    //   double rayDirX = dirX + planeX * cameraX;
    //   double rayDirY = dirY + planeY * cameraX;
	// }
	// printf("hi%f", P->playerX);
	return (0);
}
