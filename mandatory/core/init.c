/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jole <jole@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 18:47:45 by jole              #+#    #+#             */
/*   Updated: 2023/06/02 17:39:36 by jole             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"
#include "parsing.h"

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
		P->dir_x = -1;
		P->plane_y = 0.66;
	}
	else if (elements->orientation == 'E')
	{
		P->dir_x = 1;
		P->plane_y = -0.66;
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
		ft_putstr_fd("Error\nCould not load image\n", 2);
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

	load_image(P, P->texture[0], elements->south, &img);
	load_image(P, P->texture[1], elements->north, &img);
	load_image(P, P->texture[2], elements->east, &img);
	load_image(P, P->texture[3], elements->west, &img);
}
