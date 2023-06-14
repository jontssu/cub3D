/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texturing_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jole <jole@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/04 06:32:32 by leklund           #+#    #+#             */
/*   Updated: 2023/06/05 15:37:52 by jole             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



#include "cub3D_bonus.h"

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
}

int	choose_texture(t_dda *dda)
{
	int	tex_num;

	if (dda->hit == 2)
		return (5);
	if (dda->hit == 3)
		return (4);
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

void	add_line_to_buff(t_player *P, t_dda *dda, t_tex *tex)
{
	int		y;
	y = dda->draw_start;
	
	while (y < dda->draw_end)
	{
		tex->tex_y = (int)tex->tex_pos & (TEX_HEIGHT - 1);
		tex->tex_pos += tex->step;
		tex->color = P->texture[tex->tex_num] \
		[TEX_HEIGHT * tex->tex_y + tex->tex_x];
		P->buf[y][dda->x] = tex->color;
		y++;
	}
}

void	texture(t_player *P, t_dda *dda)
{
	t_tex	tex;

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
	add_line_to_buff(P, dda, &tex);
}
