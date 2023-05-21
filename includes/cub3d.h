/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leklund <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 05:52:22 by leklund           #+#    #+#             */
/*   Updated: 2023/05/19 05:52:24 by leklund          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef CUB3D_H
# define CUB3D_H

# include <stdio.h>
# include <mlx.h>
# include <stdlib.h>
# include <math.h>

typedef struct s_player{
	double	playerX;
	double	playerY;
	double	dirX;
	double	dirY;
	double	planeX;
	double	planeY;
	char	**map;
	int		ResX;
	int		ResY;
	void	*img;
	void	*reset_img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	void	*mlx;
	void	*mlx_win;

}				t_player;

int	ray_cast(t_player *P);
#endif

