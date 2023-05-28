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


void	load_image(t_player *P, int *texture, char *path, t_img *img)
{
	img->img = mlx_xpm_file_to_image(P->mlx, path, &img->img_width, &img->img_height);
	img->data = (int *)mlx_get_data_addr(img->img, &img->bpp, &img->size_l, &img->endian);
	for (int y = 0; y < img->img_height; y++)
	{
		for (int x = 0; x < img->img_width; x++)
		{
			texture[img->img_width * y + x] = img->data[img->img_width * y + x];
		}
	}
	mlx_destroy_image(P->mlx, img->img);
}

void	load_texture(t_player *P)
{
	t_img	img;
	int i;

	load_image(P, P->texture[0], "./texture/bluestone.xpm", &img);
	load_image(P, P->texture[1], "./texture/eagle.xpm", &img);
	load_image(P, P->texture[2], "./texture/greystone.xpm", &img);
	load_image(P, P->texture[3], "./texture/redbrick.xpm", &img);
	i = 0;
	while (i < 4)
	{
		if (P->texture[i] == NULL)
		{
			printf("Exit error\n");	
		}
		i++;
	}
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
	player.img.img = mlx_new_image(player.mlx, screenWidth, screenHeight);
	// player.reset_img = mlx_new_image(player.mlx, screenWidth, screenHeight);
	player.img.data = (int *)mlx_get_data_addr(player.img.img, &player.img.bpp, &player.img.size_l,
								&player.img.endian);
	ft_bzero(player.buf, screenWidth * screenHeight);
	ft_bzero(player.texture, 4 * texHeight * texWidth);
	load_texture(&player);

	ray_cast(&player);
	mlx_hook(player.mlx_win, 17, 0, red_cross_close, &player.mlx);
	mlx_put_image_to_window(player.mlx, player.mlx_win, player.img.img, 0, 0);
	mlx_hook(player.mlx_win, 2, 1L << 0, key_pressed, &player);
	mlx_loop(player.mlx);


	free_elements(&elements);
	return (0);
}
