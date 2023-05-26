/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jole <jole@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 19:39:14 by jole              #+#    #+#             */
/*   Updated: 2023/05/26 15:16:05 by jole             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"
#include "parsing.h"

void	init(t_player *P, t_parser *elements)
{
	P->playerX = 6;
	P->playerY = 6;
	P->dirX = -1;
	P->dirY = 0;
	P->planeX = 0;
	P->planeY = 0.66;
	P->map = elements->map;
	P->cpy_map = copy2DCharArray(P->map);
}

int	main(int argc, char **argv)
{
	t_player 	player;
	t_parser	elements;

	if (argc != 2)
		error_invalid_input(1);
	parser(argv[1], &elements);
	player.mlx = mlx_init();
	if (!player.mlx)
	{
		printf("mlx_int broke\n");
		exit(1);
	}
	init(&player, &elements);
	player.mlx_win = mlx_new_window(player.mlx, screenWidth, screenHeight, "Cub3D");
	player.img = mlx_new_image(player.mlx, screenWidth, screenHeight);
	player.reset_img = mlx_new_image(player.mlx, screenWidth, screenHeight);
	player.addr = mlx_get_data_addr(player.img, &player.bits_per_pixel, &player.line_length,
								&player.endian);
									char	*texture[8];
	int w = texWidth;
	int h = texHeight;
	texture[0] = "./texture/bluestone.xpm";
	texture[1] = "./texture/eagle.xpm";
	texture[2] = "./texture/greystone.xpm";
	texture[3] = "./texture/redbrick.xpm";
	player.texture[0] = mlx_xpm_file_to_image(player.mlx, texture[0], &w, &h);
	player.texture[1] = mlx_xpm_file_to_image(player.mlx, texture[1], &w, &h);
	player.texture[2] = mlx_xpm_file_to_image(player.mlx, texture[2], &w, &h);
	player.texture[3] = mlx_xpm_file_to_image(player.mlx, texture[3], &w, &h);
	ray_cast(&player);
	mlx_hook(player.mlx_win, 17, 0, red_cross_close, &player.mlx);
	mlx_put_image_to_window(player.mlx, player.mlx_win, player.img, 0, 0);
	mlx_hook(player.mlx_win, 2, 1L << 0, key_pressed, &player);
	mlx_loop(player.mlx);


	free_elements(&elements);
	return (0);
}
