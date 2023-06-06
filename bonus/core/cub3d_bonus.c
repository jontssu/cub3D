/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jole <jole@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/04 06:31:24 by leklund           #+#    #+#             */
/*   Updated: 2023/06/06 13:04:59 by jole             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D_bonus.h"

void	draw_gun(t_player *player)
{
	// printf("load gun %d\n", player->gun_index);
	mlx_put_image_to_window(player->mlx, player->mlx_win, \
		player->gun[player->gun_index].img, 0, 0);
	if (player->gun_index >= 1)
		player->gun_index = 0;
	else
		player->gun_index++;

	
}

int	core_game(t_player *player)
{
	// player->minimap = copy2DCharArray(player->map);
	ray_cast(player);
	// print_map(player);
	// if (player->minimap)
	// 	free_double_pointer(player->minimap);
	draw_gun(player);
	player_move(player);
	player_rotate(player, player->rotate_left);
	player_rotate(player, player->rotate_right);
	if(player->rotate_left < 0)
	{
		player->rotate_left += 0.005;
		if(player->rotate_left > 0)
			player->rotate_left = 0;
	}
	if(player->rotate_right > 0)
	{
		player->rotate_right -= 0.005;
		if(player->rotate_right < 0)
			player->rotate_right = 0;
	}
	return (0);
}

int dest(t_player *player)
{
	(void) player;
	printf("cool\n");
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
	mlx_hook(player->mlx_win, 12, 1L << 15, dest, player);
	mlx_loop(player->mlx);
}

int	main(int argc, char **argv)
{
	t_player	player;
	t_parser	elements;

	if (argc != 2)
		error_invalid_input(1);
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
