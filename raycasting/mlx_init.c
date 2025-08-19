/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbakour <zbakour@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 21:23:13 by zbakour           #+#    #+#             */
/*   Updated: 2025/08/19 18:34:27 by zbakour          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	init_window(t_game *game)
{
	game->mlx = mlx_init();
	if (!game->mlx)
		return (ft_putstr_fd("Error initializing MLX\n", 2));
	game->win = mlx_new_window(game->mlx, SCREEN_WIDTH, MAP_HEIGHT, "Cub3D");
	if (!game->win)
		return (ft_putstr_fd("Error creating window\n", 2));
	game->img = mlx_new_image(game->mlx, SCREEN_WIDTH, MAP_HEIGHT);
	mlx_put_image_to_window(game->mlx, game->win, game->img, 0, 0);
}
