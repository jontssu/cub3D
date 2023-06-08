// /* ************************************************************************** */
// /*                                                                            */
// /*                                                        :::      ::::::::   */
// /*   sprite_bonus.c                                     :+:      :+:    :+:   */
// /*                                                    +:+ +:+         +:+     */
// /*   By: leklund <marvin@42.fr>                     +#+  +:+       +#+        */
// /*                                                +#+#+#+#+#+   +#+           */
// /*   Created: 2023/06/08 06:33:28 by leklund           #+#    #+#             */
// /*   Updated: 2023/06/08 06:33:30 by leklund          ###   ########.fr       */
// /*                                                                            */
// /* ************************************************************************** */



// #include "cub3D_bonus.h"
// void	calc_sprites(t_player *player, t_dda *dda)
// {
// 	(void) dda;
// 	// player->spriteOrder[0] = 0;
// 	// player->spriteDistance[0] = ((player->pos_x - player->sprite.x) * (player->pos_x - player->sprite.x) + (player->pos_y - player->sprite.y) * (player->pos_y - player->sprite.y)); //sqrt not taken, unneeded

// 	//translate sprite position to relative to camera
// 	double spriteX = player->sprite.x - player->pos_x;
// 	double spriteY = player->sprite.y - player->pos_y;
// 	// printf("relative to camera, spriteX[%f], spriteY[%f]\n",spriteX,spriteY);

// 	// //transform sprite with the inverse camera matrix
// 		// [ planeX   dirX ] -1                                       [ dirY      -dirX ]
// 		// [               ]       =  1/(planeX*dirY-dirX*planeY) *   [                 ]
// 		// [ planeY   dirY ]                                          [ -planeY  planeX ]
// 	double invDet = 1.0 / (player->plane_x * player->dir_y - player->dir_x * player->plane_y); //required for correct matrix multiplication

// 	double transformX = invDet * (player->dir_y * spriteX - player->dir_x * spriteY);
// 	double transformY = invDet * (-player->plane_y * spriteX + player->plane_x * spriteY); //this is actually the depth inside the screen, that what Z is in 3D, the distance of sprite to player, matching sqrt(spriteDistance[i])

// 	int spriteScreenX = -1 / (int)((WIDTH / 2) * (1 + transformX / transformY));
// 	// printf("invDet[%f], transformX[%f], transformY[%f], spriteScreenX[%d]\n",invDet,transformX, transformY, spriteScreenX);
// 	// (void) spriteScreenX;

// 	//parameters for scaling and moving the sprites
// 	#define uDiv 1
// 	#define vDiv 1
// 	#define vMove 0.0
// 	int vMoveScreen = (int)(vMove / transformY);
// 	// printf("vMoveScreen[%d]\n",vMoveScreen);

// 	// //calculate height of the sprite on screen
// 	int spriteHeight = (int)fabs((HEIGHT / transformY) / vDiv); //using "transformY" instead of the real distance prevents fisheye	
// 	//calculate lowest and highest pixel to fill in current stripe
// 	int drawStartY = -spriteHeight / 2 + HEIGHT / 2 + vMoveScreen;
// 	if(drawStartY < 0)
// 		drawStartY = 0;
// 	int drawEndY = spriteHeight / 2 + HEIGHT / 2 + vMoveScreen;
// 	if(drawEndY >= HEIGHT)
// 		drawEndY = HEIGHT - 1;
// 	// printf("spriteHeight[%d], drawStartY[%d], drawEndY[%d]\n",spriteHeight,drawStartY, drawEndY);
// 	//calculate width of the sprite
// 	int spriteWidth = (int)fabs((HEIGHT / transformY) / uDiv);
// 	int drawStartX = -spriteWidth / 2 + spriteScreenX;
// 	if(drawStartX < 0)
// 		drawStartX = 0;
// 	int drawEndX = spriteWidth / 2 + spriteScreenX;
// 	if(drawEndX >= WIDTH)
// 		drawEndX = WIDTH - 1;
// 	// printf("spriteWidth[%d], drawStartX[%d], drawEndX[%d]\n",spriteWidth,drawStartX, drawEndX);
	
// 	// loop through every vertical stripe of the sprite on screen
// 	for(int stripe = drawStartX; stripe < drawEndX; stripe++)
// 		{
// 			int texX = (int)((256 * (stripe - (-spriteWidth / 2 + spriteScreenX)) * TEX_WIDTH / spriteWidth) / 256);
// 			//the conditions in the if are:
// 			//1) it's in front of camera plane so you don't see things behind you
// 			//2) it's on the screen (left)
// 			//3) it's on the screen (right)
// 			//4) ZBuffer, with perpendicular distance
// 			// printf("stripe[%d], BUF[%f]\n", stripe, player->ZBuffer[stripe]);
// 			if(transformY > 0 && stripe > 0 && stripe < WIDTH && transformY < player->ZBuffer[stripe])
// 			{
// 				for(int y = drawStartY; y < drawEndY; y++) //for every pixel of the current stripe
// 				{
// 					int d = (y-vMoveScreen) * 256 - HEIGHT * 128 + spriteHeight * 128; //256 and 128 factors to avoid floats
// 					int texY = ((d * TEX_HEIGHT) / spriteHeight) / 256;
// 					int color = player->texture[player->sprite.texture][TEX_WIDTH * texY + texX]; //get current color from the texture
// 					// printf("stripe[%d], BUF[%f]\n", stripe, player->ZBuffer[stripe]);	
// 					if((color & 0x00FFFFFF) != 0) player->buf[y][stripe] = color; //paint pixel if it isn't black, black is the invisible color
// 				}
// 			}
// 		}
// }
