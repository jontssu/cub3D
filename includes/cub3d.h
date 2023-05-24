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
	char	**cpy_map;
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
	int h;
	int lineHeight;
	//calculate lowest and highest pixel to fill in current stripe
    int drawStart;
    int drawEnd;
}				t_dda;

//KEY_HANDLE
int key_pressed(int keycode, void *param);
int	red_cross_close(void);
void player_move1(t_player *P, double x, double y);
void player_move2(t_player *P, double x, double y);
void player_rotate(t_player *P, double x);

int	ray_cast(t_player *P);
void print_map(t_player *P);
char** copy2DCharArray(char** arr);
# include <string.h>
#endif

