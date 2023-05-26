/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leklund <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 11:55:32 by leklund           #+#    #+#             */
/*   Updated: 2023/05/24 11:55:34 by leklund          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H
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


typedef struct s_player{
	double	playerX;
	double	playerY;
	double	dirX;
	double	dirY;
	double	planeX;
	double	planeY;
	char	**map;
	char	**cpy_map;
	void	*img;
	void	*reset_img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	void	*mlx;
	void	*mlx_win;
	void	*texture[8];
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

typedef struct s_parser
{
	char	*north;
	char	*south;
	char	*west;
	char	*east;
	int		floor[4];
	int		ceiling[4];
	char	**map;
}	t_parser;

//Parser
int		parser(char *file, t_parser *elements);
void	check_config_file_name(char *file);
int		set_elements(char **split, t_parser *elements);
void	check_elements(t_parser *elements);
int		get_map(char **split, t_parser *elements);
void	fill_with_x(int max_size, t_parser *elements);

//Map check
void	map_check(t_parser *elements);
void	valid_chars_check(t_parser *elements);

//Error handling
int		error_argument_count(void);
void	error_cub_file(void);
void	error_in_colors(void);
void	error_in_path(void);
void	error_no_color_setting(void);
void	error_invalid_char(void);
void	error_start_position(void);

//Helpers
void	free_double_pointer(char **array);

//KEY_HANDLE
int key_pressed(int keycode, void *param);
int	red_cross_close(void);
void player_move(t_player *P, double x, double y, int type);
void player_rotate(t_player *P, double x);

//texuring
void	texture(t_player *P, t_dda *dda);

int	ray_cast(t_player *P);
void print_map(t_player *P);
char** copy2DCharArray(char** arr);
# include <string.h>
#endif
	
