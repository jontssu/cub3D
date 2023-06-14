/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jole <jole@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/04 06:31:24 by leklund           #+#    #+#             */
/*   Updated: 2023/06/14 17:30:10 by jole             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D_bonus.h"

void	draw_gun(t_player *player)
{
	if (player->shoot)
	{
		player->shoot -= player->d_time;
		if (player->shoot <= 0)
		{
			if (player->gun_index >= 4)
			{
				player->gun_index = 0;
				player->shoot = 0;
			}
			else
			{
				player->gun_index++;
				player->shoot = 0.05;
			}
		}
	}
	mlx_put_image_to_window(player->mlx, player->mlx_win, \
		player->gun[player->gun_index].img, \
		WIDTH / 2 - 70, HEIGHT - GUN_HEIGHT);
}

void	get_time(t_player *player)
{
	struct timeval	t;
	double			elapsed;

	gettimeofday(&t, NULL);
	elapsed = (t.tv_sec - player->time.tv_sec) * 1000;
	elapsed += (t.tv_usec - player->time.tv_usec) / 1000;
	player->d_time = elapsed / 1000;
	player->time = t;
}

int	core_game(t_player *player)
{
	if (player->cpy_map)
		free_double_pointer(player->cpy_map);
	player->cpy_map = copy_2d_array(player->map);
	ray_cast(player);
	get_time(player);
	draw_gun(player);
	player_move(player);
	player_rotate(player, player->rotate_left);
	player_rotate(player, player->rotate_right);
	if (player->rotate_left < 0)
	{
		player->rotate_left += 0.005;
		if (player->rotate_left > 0)
			player->rotate_left = 0;
	}
	if (player->rotate_right > 0)
	{
		player->rotate_right -= 0.005;
		if (player->rotate_right < 0)
			player->rotate_right = 0;
	}
	return (0);
}

void	mlxing(t_player *player, t_parser *elements)
{
	player->mlx_win = mlx_new_window(player->mlx, WIDTH, HEIGHT, "Cub3D");
	if (!player->mlx_win)
		free_all(player);
	player->img.img = mlx_new_image(player->mlx, WIDTH, HEIGHT);
	if (!player->img.img)
		free_all(player);
	player->img.data = (int *)mlx_get_data_addr(player->img.img, \
	&player->img.bpp, &player->img.size_l, &player->img.endian);
	ft_bzero(player->buf, WIDTH * HEIGHT);
	ft_bzero(player->texture, 8 * TEX_HEIGHT * TEX_WIDTH);
	load_texture(player, elements);
	mlx_hook(player->mlx_win, 17, 0, free_all, player);
	mlx_put_image_to_window(player->mlx, player->mlx_win, \
	player->img.img, 0, 0);
	mlx_loop_hook(player->mlx, core_game, player);
	mlx_hook(player->mlx_win, 2, 1L << 0, key_pressed, player);
	mlx_hook(player->mlx_win, 3, 1L << 1, key_release, player);
	mlx_hook(player->mlx_win, 6, 1L << 6, mouse_rotate, player);
	mlx_loop(player->mlx);
}

int	main(int argc, char **argv)
{
	t_player	player;
	t_parser	elements;

	if (argc != 2)
		error_invalid_input(1);
	if (WIDTH < 300 || HEIGHT < 300)
	{
		printf("bad Window size\n");
		return (1);
	}
	parser(argv[1], &elements);
	player.mlx = mlx_init();
	if (!player.mlx)
	{
		printf("mlx_init broke\n");
		free_all(&player);
	}
	init(&player, &elements);
	mlxing(&player, &elements);
	return (0);
}
