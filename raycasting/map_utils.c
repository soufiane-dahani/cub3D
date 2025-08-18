/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sodahani <sodahani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 22:49:02 by zbakour           #+#    #+#             */
/*   Updated: 2025/08/18 10:04:15 by sodahani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	draw_background(t_game *game)
{
	int		bits_per_pixel;
	int		size_line;
	int		endian;
	char	*data;
	int		gray;

	data = mlx_get_data_addr(game->img, &bits_per_pixel, &size_line, &endian);
	gray = 0x808080;
	for (int y = 0; y < MAP_HEIGHT; y++)
		for (int x = 0; x < SCREEN_WIDTH; x++)
			put_pixel(data, x, y, gray, size_line);
	mlx_put_image_to_window(game->mlx, game->win, game->img, 0, 0);
}

void	draw_player(t_game *game)
{
	int		red;
	char	*data;
	int		player_w;
	int		player_h;
	int		px;
	int		py;

	red = 0xFF0000;
	int bpp, line_length, endian;
	data = mlx_get_data_addr(game->img, &bpp, &line_length, &endian);
	player_w = (TILE_SIZE / 4) / 4;
	player_h = (TILE_SIZE / 4) / 4;
	px = game->player_x / 8;
	py = game->player_y / 8;
	if (py > TILE_SIZE / 8 && py < MAP_HEIGHT)
		draw_tile(game, game->mlx, game->win, px, py, player_w / 2, red);
}

void	draw_map_walls(t_game *game)
{
	int		yellow;
	char	*data;
	int		map_x;
	int		map_y;
	int		x;
	int		y;
	int bpp, line_length, endian;

	yellow = 0xFFFF00;
	data = mlx_get_data_addr(game->img, &bpp, &line_length, &endian);
	// draw_background(game);
	map_x = game->map_width;
	map_y = game->map_height;
	x = 0;
	y = 0;
	for (int i = 0; i < map_y; i++)
	{
		for (int j = 0; j < map_x; j++)
		{
			if (game->map_section[i][j] == '1')
				draw_tile(game, game->mlx, game->win, j * (TILE_SIZE / 8), i
					* (TILE_SIZE / 8), (TILE_SIZE / 8), yellow);
			x += TILE_SIZE - 8;
		}
		y += TILE_SIZE - 8;
	}
	mlx_put_image_to_window(game->mlx, game->win, game->img, 0, 0);
}

void	draw_map(t_game *game)
{
	int		yellow;
	char	*data;
	int		map_x;
	int		map_y;
	int		x;
	int		y;

	yellow = 0xFFFF00;
	int bpp, line_length, endian;
	data = mlx_get_data_addr(game->img, &bpp, &line_length, &endian);
	// draw_background(game);
	map_x = game->map_width;
	map_y = game->map_height;
	x = 0;
	y = 0;
	for (int i = 0; i < map_y; i++)
	{
		for (int j = 0; j < map_x; j++)
		{
			if (game->map_section[i][j] == '1')
				draw_tile(game, game->mlx, game->win, j * (TILE_SIZE / 8), i
					* (TILE_SIZE / 8), (TILE_SIZE / 8), yellow);
			else
				draw_tile(game, game->mlx, game->win, j * (TILE_SIZE / 8), i
					* (TILE_SIZE / 8), (TILE_SIZE / 8), 0x000000);
			x += (TILE_SIZE / 8);
		}
		y += (TILE_SIZE / 8);
	}
	mlx_put_image_to_window(game->mlx, game->win, game->img, 0, 0);
}

void	draw_map_bg(t_game *game)
{
	int		yellow;
	char	*data;
	int		map_x;
	int		map_y;
	int		x;
	int		y;

	yellow = 0xFFF900;
	int bpp, line_length, endian;
	data = mlx_get_data_addr(game->img, &bpp, &line_length, &endian);
	map_x = game->map_width;
	map_y = game->map_height;
	x = 0;
	y = 0;
	for (int i = 0; i < map_y; i++)
	{
		for (int j = 0; j < map_x; j++)
		{
			if (game->map_section[i][j] != '1')
				draw_tile(game, game->mlx, game->win, j * (TILE_SIZE / 8), i
					* (TILE_SIZE / 8), (TILE_SIZE / 8), game->ceiling);
			x += (TILE_SIZE / 8);
		}
		y += (TILE_SIZE / 8);
	}
	mlx_put_image_to_window(game->mlx, game->win, game->img, 0, 0);
}
