/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jole <jole@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/04 07:42:43 by leklund           #+#    #+#             */
/*   Updated: 2023/06/15 14:57:43 by jole             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_BONUS_H
# define CUB3D_BONUS_H
# include "libft.h"
# include "parsing_bonus.h"
# include <stdio.h>
# include <mlx.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdlib.h>
# include <math.h>
# include <time.h>
# include <sys/time.h>

//Player
# define BODY 0.1
# define SPEED 0.05
# define ROT_SPEED 0.05

//Mac key values
# define KEY_W 13
# define KEY_S 1
# define KEY_A 0
# define KEY_D 2
# define KEY_LEFT 124
# define KEY_RIGHT 123
# define KEY_ESC 53
# define KEY_OPEN 14 

//Graphics
# define WIDTH 1680
# define HEIGHT 900
# define TEX_WIDTH 64
# define TEX_HEIGHT 64
# define GUN_HEIGHT 140
# define GUN_WIDTH 140
# define MAP_SIZE 7

typedef struct s_sprite
{
	double		x;
	double		y;
	int			texture;
}				t_sprite;

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
	double			pos_x;
	double			pos_y;
	double			dir_x;
	double			dir_y;
	double			plane_x;
	double			plane_y;
	int				move_w;
	int				move_s;
	int				move_a;
	int				move_d;
	double			rotate_left;
	double			rotate_right;
	int				open_door;
	int				prev_rot_x;
	void			*mlx;
	void			*mlx_win;
	t_img			img;
	int				texture[5][TEX_HEIGHT * TEX_WIDTH];
	int				buf[HEIGHT][WIDTH];
	int				gun_index;
	t_img			gun[5];
	double			shoot;
	double			d_time;
	struct timeval	time;
	int				ceiling;
	int				floor;
	int				count_y;
	int				count_x;
	int				size;
	int				r_size;
	char			**map;
	char			**cpy_map;
	t_parser		*elements;
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

//utils
int		create_trgb_arr(int arr[4]);
void	draw_gun(t_player *player);
void	get_time(t_player *player);

//init
void	update_gun(t_player *player);
void	init(t_player *P, t_parser *elements);
void	load_texture(t_player *P, t_parser *elements);

//KEY_HANDLE
int		key_pressed(int keycode, t_player *param);
int		free_all(t_player *param, int exit_code);
void	player_move(t_player *P);
void	player_rotate(t_player *P, double x);
int		key_release(int keycode, t_player *param);
int		mouse_rotate(int x, int y, t_player *player);
int		open_door(t_player *p);

//texturing
void	texture(t_player *P, t_dda *dda);
void	draw(t_player *P);

//Ray_casting
int		ray_cast(t_player *P);

//sprites
void	calc_sprites(t_player *player, t_dda *dda);

//minimap
void	minimap(t_player *p);
char	**copy_2d_array(t_player *p, char **arr);

#endif