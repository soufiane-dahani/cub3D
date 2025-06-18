/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbakour <zbakour@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 21:23:13 by zbakour           #+#    #+#             */
/*   Updated: 2025/06/17 15:21:08 by zbakour          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void init_window(t_game *game)
{
    game->mlx = mlx_init();
    if (!game->mlx)
        return (ft_putstr_fd("Error initializing MLX\n", 2));
    game->win = mlx_new_window(game->mlx, SCREEN_WIDTH, MAP_HEIGHT, "Cub3D");
    if (!game->win)
        return (ft_putstr_fd("Error creating window\n", 2));
    game->img = mlx_new_image(game->mlx, SCREEN_WIDTH, MAP_HEIGHT);

    int bits_per_pixel;
    int size_line;
    int endian;
    char *data = mlx_get_data_addr(game->img, &bits_per_pixel, &size_line, &endian);
    int gray = 0x808080;
    for (int y = 0; y < MAP_HEIGHT; y++)
        for (int x = 0; x < SCREEN_WIDTH; x++)
            put_pixel(data, x, y, gray, size_line);

    mlx_put_image_to_window(game->mlx, game->win, game->img, 0, 0);
}