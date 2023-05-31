/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_casting.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jole <jole@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 06:52:41 by leklund           #+#    #+#             */
/*   Updated: 2023/05/29 18:15:39 by jole             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAY_CASTING_H
# define RAY_CASTING_H
# include "libft.h"
# include <stdio.h>
# include <mlx.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdlib.h>
# include <math.h>

//Player
# define BODY 0.25
# define SPEED 0.1
# define ROT_SPEED 0.1


//Mac key values
# define KEY_W 13
# define KEY_S 1
# define KEY_A 0
# define KEY_D 2
# define KEY_LEFT 124
# define KEY_RIGHT 123
# define KEY_ESC 53


# define WIDTH 640
# define HEIGHT 480
# define TEX_WIDTH 64
# define TEX_HEIGHT 64


typedef struct s_img
{
	void	*img;
	int		*data;

	int		size_l;
	int		bpp;
	int		endian;
	int		img_width;
	int		img_height;
}				t_img;

typedef struct s_tex
{
	int		tex_num;
	double	wall_x;
	int		tex_x;
	double	tex_pos;
	int		tex_y;
	double	step;
	int		color;
}				t_tex;

typedef struct s_player{
	double	pos_x;
	double	pos_y;
	double	dir_x;
	double	dir_y;
	double	plane_x;
	double	plane_y;
	void	*mlx;
	void	*mlx_win;
	t_img	img;
	int		texture[4][TEX_HEIGHT * TEX_WIDTH];
	int		buf[HEIGHT][WIDTH];
	int		ceiling;
	int		floor;
	char	**map;
	char	**cpy_map;
}				t_player;

//Digital differential analysis ;D
typedef struct s_dda
{
	int		x;
	double	camera_x;
	double	ray_dir_x;
	double	ray_dir_y;
	double	delta_dist_x;
	double	delta_dist_y;
	double	tot_dist_x;
	double	tot_dist_y;
	double	perp_wall_dist;
	int		step_x;
	int		step_y;
	int		hit;
	int		side;
	int		map_x;
	int		map_y;
	int		line_height;
	int		draw_start;
	int		draw_end;
}					t_dda;

//KEY_HANDLE
int		key_pressed(int keycode, void *param);
int		red_cross_close(void);
int		esc_close_window(void);
void	player_move(t_player *P, double x, double y, int type);
void	player_rotate(t_player *P, double x);

//texuring
void	texture(t_player *P, t_dda *dda);
void	draw(t_player *P);

//Ray_casting
int		ray_cast(t_player *P);

//EXTRA REMOVE <=========================== OIIIIII!!!!!!!!!!!!!
//EXTRA REMOVE <=========================== OIIIIII!!!!!!!!!!!!!
//EXTRA REMOVE <=========================== OIIIIII!!!!!!!!!!!!!
void	print_map(t_player *P);
char**	copy2DCharArray(char** arr);
# include <string.h>
#endif
