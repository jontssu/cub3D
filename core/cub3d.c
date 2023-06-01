/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jole <jole@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 19:39:14 by jole              #+#    #+#             */
/*   Updated: 2023/06/01 18:55:03 by jole             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "parsing.h"

int	core_game(t_player *player)
{
	ray_cast(player);
	player_move(player);
	player_rotate(player, player->rotate);
	return (0);
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
		printf("mlx_int broke\n");
		exit(1);
	}
	init(&player, &elements);
	player.mlx_win = mlx_new_window(player.mlx, WIDTH, HEIGHT, "Cub3D");
	player.img.img = mlx_new_image(player.mlx, WIDTH, HEIGHT);
	player.img.data = (int *)mlx_get_data_addr(player.img.img, \
	&player.img.bpp, &player.img.size_l, &player.img.endian);
	ft_bzero(player.buf, WIDTH * HEIGHT);
	ft_bzero(player.texture, 4 * TEX_HEIGHT * TEX_WIDTH);
	load_texture(&player, &elements);
	ray_cast(&player);
	mlx_hook(player.mlx_win, 17, 0, free_all, &player);
	mlx_put_image_to_window(player.mlx, player.mlx_win, player.img.img, 0, 0);
	mlx_hook(player.mlx_win, 2, 1L << 0, key_pressed, &player);
	mlx_loop_hook(player.mlx, &core_game, &player);
	mlx_hook(player.mlx_win, 3, 1L << 1, key_release, &player);
	mlx_loop(player.mlx);
	return (0);
}
