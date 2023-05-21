/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leklund <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 13:17:21 by leklund           #+#    #+#             */
/*   Updated: 2023/05/18 13:17:22 by leklund          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "cub3d.h"

int	rec_cross_close(void)
{
	exit(0);
}

void init(t_player *P)
{
	P->playerX = 12;
	P->playerY = 2;
	P->dirX = -0.45;
	P->dirY = 0;
	P->planeX = 0;
	P->planeY = 0.66;
	P->ResX = 600;
	P->ResY = 400;
	int i, j;

    P->map = (char**)malloc(sizeof(char*) * 15);
    i = 0;
    while(i < 14) {
        P->map[i] = (char*)malloc(sizeof(char) * 16);
        j = 0;
        while(j < 15) {
            if(i == 0 || i == 13 || j == 0 || j == 14) {
                P->map[i][j] = '1';
            } else {
                P->map[i][j] = '0';
            }
            j++;
        }
        P->map[i][j] = '\0';
        i++;
    }
	// P->map[1][5] = '1';
    P->map[i] = NULL;
    i = 0;
    while(P->map[i] != NULL) {
        printf("%s\n", P->map[i]);
        i++;
    }
}

void player_move(t_player *P, double x, double y)
{
	// printf("x: %f, y: %f\n", x, y);

	P->playerX += x;
	P->playerY += y;
	ray_cast(P);
	mlx_put_image_to_window(P->mlx, P->mlx_win, P->reset_img, 0, 0);
	mlx_put_image_to_window(P->mlx, P->mlx_win, P->img, 0, 0);

}
int key_pressed(int keycode, void *param)
{
	(void) param;
	// printf("key-pressed: %d\n", keycode);
	if(keycode == 0)//left
		player_move(param, -0.1, 0);
	else if (keycode == 13)//up
		player_move(param, 0, -0.1);
	else if (keycode == 2)//right
		player_move(param, 0.1, 0);
	else if (keycode == 1)//down
		player_move(param, 0.0, 0.1);
	return (0);
}

int key_released(int keycode, void *param)
{
	(void) param;
	(void) keycode;
	// printf("key-released: %d\n", keycode);
	return (0);

}

int	main(void)
{
	t_player player;

	player.mlx = mlx_init();
	if (!player.mlx)
	{
		printf("mlx_int broke\n");
		exit(1);
	}
	init(&player);
	player.mlx_win = mlx_new_window(player.mlx, player.ResX, player.ResY, "Cub3D");
	player.img = mlx_new_image(player.mlx, player.ResX, player.ResY);
	player.reset_img = mlx_new_image(player.mlx, player.ResX, player.ResY);
	player.addr = mlx_get_data_addr(player.img, &player.bits_per_pixel, &player.line_length,
								&player.endian);
	ray_cast(&player);
	// mlx_loop_hook(mlx, ray_cast, &player);
	mlx_hook(player.mlx_win, 17, 0, rec_cross_close, &player.mlx);
	mlx_put_image_to_window(player.mlx, player.mlx_win, player.img, 0, 0);
	mlx_hook(player.mlx_win, 2, 1L << 0, key_pressed, &player);
	mlx_hook(player.mlx_win, 3, 1L << 1, key_released, &player);
	mlx_loop(player.mlx);

	return (0);
}