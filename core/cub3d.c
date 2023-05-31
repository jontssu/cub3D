/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jole <jole@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 19:39:14 by jole              #+#    #+#             */
/*   Updated: 2023/05/29 16:11:59 by jole             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"
#include "parsing.h"

int	create_trgb(int arr[4])
{
	return (0 << 24 | arr[0] << 16 | arr[1] << 8 | arr[3]);
}

void	init(t_player *P, t_parser *elements)
{
	P->pos_x = elements->start_x + 0.5;
	P->pos_y = elements->start_y + 0.5;
	P->dir_x = -1;
	P->dir_y = 0;
	P->plane_x = 0;
	P->plane_y = 0.66;
	P->map = elements->map;
	P->cpy_map = copy2DCharArray(P->map);
	P->ceiling = create_trgb(elements->ceiling);
	P->floor = create_trgb(elements->floor);
	P->map[(int)P->pos_y][(int)P->pos_x] = '.';

}


void	load_image(t_player *P, int *texture, char *path, t_img *img)
{
	int	y;
	int	x;

	img->img = mlx_xpm_file_to_image(P->mlx, path, &img->img_width, &img->img_height);
	img->data = (int *)mlx_get_data_addr(img->img, &img->bpp, &img->size_l, &img->endian);
	y = 0;
	while (y < img->img_height)
	{
		x = 0;
		while (x < img->img_width)
		{
			texture[img->img_width * y + x] = img->data[img->img_width * y + x];
			x++;
		}
		y++;
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
	player.mlx_win = mlx_new_window(player.mlx, WIDTH, HEIGHT, "Cub3D");
	player.img.img = mlx_new_image(player.mlx, WIDTH, HEIGHT);
	// player.reset_img = mlx_new_image(player.mlx, screenWidth, screenHeight);
	player.img.data = (int *)mlx_get_data_addr(player.img.img, &player.img.bpp, &player.img.size_l,
								&player.img.endian);
	ft_bzero(player.buf, WIDTH * HEIGHT);
	ft_bzero(player.texture, 4 * TEX_HEIGHT * TEX_WIDTH);
	load_texture(&player);

	ray_cast(&player);
	mlx_hook(player.mlx_win, 17, 0, red_cross_close, &player.mlx);
	// mlx_loop_hook(player.mlx, ray_cast, &player);
	mlx_put_image_to_window(player.mlx, player.mlx_win, player.img.img, 0, 0);
	mlx_hook(player.mlx_win, 2, 1L << 0, key_pressed, &player);
	mlx_loop(player.mlx);


	free_elements(&elements);
	return (0);
}
