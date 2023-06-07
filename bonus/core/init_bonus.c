/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jole <jole@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/04 06:31:32 by leklund           #+#    #+#             */
/*   Updated: 2023/06/06 13:13:47 by jole             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D_bonus.h"

int	create_trgb(int arr[4])
{
	return (0 << 24 | arr[0] << 16 | arr[1] << 8 | arr[3]);
}

void	determine_dir(t_player *P, t_parser *elements)
{
	if (elements->orientation == 'N')
	{
		P->dir_y = -1;
		P->plane_x = -0.66;
	}
	else if (elements->orientation == 'S')
	{
		P->dir_y = 1;
		P->plane_x = 0.66;
	}
	else if (elements->orientation == 'W')
	{
		P->dir_x = 1;
		P->plane_y = -0.66;
	}
	else if (elements->orientation == 'E')
	{
		P->dir_x = -1;
		P->plane_y = 0.66;
	}
}

void	init(t_player *P, t_parser *elements)
{
	P->move_w = 0;
	P->move_s = 0;
	P->move_a = 0;
	P->move_d = 0;
	P->rotate_left = 0;
	P->rotate_right = 0;
	P->elements = elements;
	P->pos_x = elements->start_x + 0.5;
	P->pos_y = elements->start_y + 0.5;
	P->dir_x = 0;
	P->dir_y = 0;
	P->plane_x = 0;
	P->plane_x = 0;
	determine_dir(P, elements);
	P->map = elements->map;
	// P->cpy_map = copy2DCharArray(P->map);
	P->ceiling = create_trgb(elements->ceiling);
	P->floor = create_trgb(elements->floor);
	P->map[(int)P->pos_y][(int)P->pos_x] = '.';
}

void	load_image(t_player *P, int *texture, char *path, t_img *img)
{
	int	y;
	int	x;

	img->img = mlx_xpm_file_to_image(P->mlx, path, \
	&img->img_width, &img->img_height);
	if (!img->img)
	{
		printf("could not load image %s\n", path);
		free_all(P);
	}
	img->data = (int *)mlx_get_data_addr(img->img, \
	&img->bpp, &img->size_l, &img->endian);
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

void	load_texture(t_player *P, t_parser *elements)
{
	t_img	img;

	// printf("LOAD_TEXTURE\n");
	load_image(P, P->texture[0], elements->south, &img);
	load_image(P, P->texture[1], elements->north, &img);
	load_image(P, P->texture[2], elements->east, &img);
	load_image(P, P->texture[3], elements->west, &img);
	P->gun_index = 0;
	P->gun[0].img = mlx_xpm_file_to_image(P->mlx, "textures/gun3.xpm", \
	&P->gun[0].img_width, &P->gun[0].img_height);
	if (!P->gun[0].img)
	{
		printf("could not load image %s\n", "textures/gun0.xpm");
		free_all(P);
	}
	else
		printf("load image %s\n", "textures/gun3.xpm");
	P->gun[1].img = mlx_xpm_file_to_image(P->mlx, "textures/gun0.xpm", \
	&P->gun[1].img_width, &P->gun[1].img_height);
	if (!P->gun[1].img)
	{
		printf("could not load image %s\n", "textures/gun3.xpm");
		free_all(P);
	}
	else
		printf("load image %s\n", "textures/gun3.xpm");

	load_image(P, P->texture[4], elements->door_o, &img);
	load_image(P, P->texture[5], elements->door_c, &img);
	// printf("LOAD_TEXTURE\n");
}
