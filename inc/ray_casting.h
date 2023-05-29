/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_casting.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leklund <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 06:52:41 by leklund           #+#    #+#             */
/*   Updated: 2023/05/29 06:52:42 by leklund          ###   ########.fr       */
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

//Mac key values
# define KEY_W 13
# define KEY_S 1
# define KEY_A 0
# define KEY_D 2
# define KEY_LEFT 124
# define KEY_RIGHT 123


# define screenWidth 640
# define screenHeight 480
# define texWidth 64
# define texHeight 64


typedef struct	s_img
{
	void	*img;
	int		*data;

	int		size_l;
	int		bpp;
	int		endian;
	int		img_width;
	int		img_height;
}				t_img;

typedef struct s_player{
	double	playerX;
	double	playerY;
	double	dirX;
	double	dirY;
	double	planeX;
	double	planeY;
	char	**map;
	char	**cpy_map;
	// void	*img;
	// void	*reset_img;
	// char	*addr;
	// int		bits_per_pixel;
	// int		line_length;
	// int		endian;
	t_img	img;
	int		buf[screenHeight][screenWidth];
	void	*mlx;
	void	*mlx_win;
	int		texture[4][texHeight * texWidth];
	int		re_buf;
	int		floor;
	int		ceiling;
}				t_player;

typedef struct s_dda
{
	int	x;
	double cameraX; //cam x pos
	double rayDirX; // direction to work with the ray/vector from player to make FOV
	double rayDirY;
	double deltaDistX;//the amount to increase measure vector
	double deltaDistY;
	double sideDistX;//mesaure vector total
	double sideDistY;
	double perpWallDist; //the length from POV to wall
	int stepX; //what direction to step into x or y
	int stepY;
	int hit; //was there a wall hit?
	int side; //was a NS or a EW wall hit?
	int mapX; //current vector hit pos
	int mapY;
	//Calculate height of line to draw on screen
	int lineHeight;
	//calculate lowest and highest pixel to fill in current stripe
    int drawStart;
    int drawEnd;
}					t_dda;

//KEY_HANDLE
int key_pressed(int keycode, void *param);
int	red_cross_close(void);
void player_move(t_player *P, double x, double y, int type);
void player_rotate(t_player *P, double x);

//texuring
void	texture(t_player *P, t_dda *dda);
void	draw(t_player *P);


int	ray_cast(t_player *P);
void print_map(t_player *P);
char** copy2DCharArray(char** arr);
# include <string.h>
#endif
