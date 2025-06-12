/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbakour <zbakour@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 22:48:03 by obarais           #+#    #+#             */
/*   Updated: 2025/06/12 14:10:47 by zbakour          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void raycasting(t_game *game)
{
	game->mlx = mlx_init();
	if (!game->mlx)
	{
		ft_putstr_fd("Error initializing MLX\n", 2);
		exit(1);
	}
	game->win = mlx_new_window(game->mlx, MAP_WIDTH, MAP_HEIGHT, "Cub3D");
	if (!game->win)
	{
		ft_putstr_fd("Error creating window\n", 2);
		exit(1);
	}
	// chose_the_angle_p(game);
	game->player_x *= TILE;
	game->player_y *= TILE;
	// mlx_hook(game->win, 2, 1L << 0, key_hook, game);
	// mlx_loop_hook(game->mlx, loop_hook, game);
	mlx_hook(game->win, 17, 0, mlx_loop_end, game->mlx);
	mlx_loop(game->mlx);
}
