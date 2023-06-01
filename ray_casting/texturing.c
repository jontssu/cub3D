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

#include "cub3d.h"

void	draw(t_player *P)
{
	int	y;
	int	x;

	y = 0;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			P->img.data[y * WIDTH + x] = P->buf[y][x];
			x++;
		}
		y++;
	}
	// mlx_put_image_to_window(P->mlx, P->mlx_win, P->img.img, 0, 0);
}

int	choose_texture(t_dda *dda)
{
	int	tex_num;

	if (dda->side == 1)
	{
		if (dda->ray_dir_y <= 0)
			tex_num = 0;
		else
			tex_num = 1;
	}
	else
	{
		if (dda->ray_dir_x <= 0)
			tex_num = 2;
		else
			tex_num = 3;
	}
	return (tex_num);
}

void	texture(t_player *P, t_dda *dda)
{
	t_tex	tex;
	int		y;

	tex.tex_num = choose_texture(dda);
	if (dda->side == 0)
		tex.wall_x = P->pos_y + dda->perp_wall_dist * dda->ray_dir_y;
	else
		tex.wall_x = P->pos_x + dda->perp_wall_dist * dda->ray_dir_x;
	tex.wall_x -= floor((tex.wall_x));
	tex.tex_x = (int)(tex.wall_x * (double)(TEX_WIDTH));
	if (dda->side == 0 && dda->ray_dir_x > 0)
		tex.tex_x = TEX_WIDTH - tex.tex_x - 1;
	if (dda->side == 1 && dda->ray_dir_y < 0)
		tex.tex_x = TEX_WIDTH - tex.tex_x - 1;
	tex.step = 1.0 * TEX_HEIGHT / dda->line_height;
	tex.tex_pos = (dda->draw_start - HEIGHT / 2 + dda->line_height / 2) \
	* tex.step;
	y = dda->draw_start;
	while (y < dda->draw_end)
	{
		tex.tex_y = (int)tex.tex_pos & (TEX_HEIGHT - 1);
		tex.tex_pos += tex.step;
		tex.color = P->texture[tex.tex_num][TEX_HEIGHT * tex.tex_y + tex.tex_x];
		P->buf[y][dda->x] = tex.color;
		y++;
	}

}