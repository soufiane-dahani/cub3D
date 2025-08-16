/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbakour <zbakour@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 22:49:02 by zbakour           #+#    #+#             */
/*   Updated: 2025/08/16 13:37:16 by zbakour          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void draw_background(t_game *game)
{
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

void draw_player(t_game *game)
{
	int red = 0xFF0000;
	int green = 0x00FF00;
	int bpp, line_length, endian;
	char *data = mlx_get_data_addr(game->img, &bpp, &line_length, &endian);

	int player_w = (TILE_SIZE / 4) / 4;
	int player_h = (TILE_SIZE / 4) / 4;

	int px = game->player_x / 8;
	int py = game->player_y / 8;

	if (py > TILE_SIZE / 8 && py < MAP_HEIGHT)
	{
		draw_tile(game, game->mlx, game->win, px, py, player_w / 2, red);

		// // for debug player direction
		// int cx = px + player_w / 2;
		// int cy = py + player_h / 2;
		// int look_x = cx + cos(game->player_angle) * 10;
		// int look_y = cy + sin(game->player_angle) * 10;
		// draw_line(game, cx, cy, look_x, look_y, 0x00FF00);
		// mlx_put_image_to_window(game->mlx, game->win, game->img, 0, 0);
	}
}

void draw_map_walls(t_game *game)
{
	int yellow = 0xFFFF00;
	int bpp, line_length, endian;
	char *data = mlx_get_data_addr(game->img, &bpp, &line_length, &endian);

	// draw_background(game);
	int map_x = game->map_width;
	int map_y = game->map_height;
	int x = 0;
	int y = 0;
	for (int i = 0; i < map_y; i++)
	{
		for (int j = 0; j < map_x; j++)
		{
			if (game->map_section[i][j] == '1')
				draw_tile(game, game->mlx, game->win, j * (TILE_SIZE / 8), i * (TILE_SIZE / 8), (TILE_SIZE / 8), yellow);
			x += TILE_SIZE - 8;
		}
		y += TILE_SIZE - 8;
	}
	mlx_put_image_to_window(game->mlx, game->win, game->img, 0, 0);
}

void draw_map(t_game *game)
{
	int yellow = 0xFFFF00;
	int bpp, line_length, endian;
	char *data = mlx_get_data_addr(game->img, &bpp, &line_length, &endian);

	// draw_background(game);
	int map_x = game->map_width;
	int map_y = game->map_height;
	int x = 0;
	int y = 0;
	for (int i = 0; i < map_y; i++)
	{
		for (int j = 0; j < map_x; j++)
		{
			if (game->map_section[i][j] == '1')
				// if (game->map_section[i][j + 1] == '1' || game->map_section[i][j - 1] == '1' || game->map_section[i - 1][j] == '1')
				draw_tile(game, game->mlx, game->win, j * (TILE_SIZE / 8), i * (TILE_SIZE / 8), (TILE_SIZE / 8), yellow);
			// else
			// 	draw_tile(game, game->mlx, game->win, j * (TILE_SIZE / 4),  i * (TILE_SIZE / 4), (TILE_SIZE / 4) - 1, yellow);
			else
				draw_tile(game, game->mlx, game->win, j * (TILE_SIZE / 8), i * (TILE_SIZE / 8), (TILE_SIZE / 8), 0x000000);
			x += (TILE_SIZE / 8);
		}
		y += (TILE_SIZE / 8);
	}
	mlx_put_image_to_window(game->mlx, game->win, game->img, 0, 0);
}

void draw_map_bg(t_game *game)
{
	int yellow = 0xFFFF00;
	int bpp, line_length, endian;
	char *data = mlx_get_data_addr(game->img, &bpp, &line_length, &endian);

	// draw_background(game);
	int map_x = game->map_width;
	int map_y = game->map_height;
	int x = 0;
	int y = 0;
	for (int i = 0; i < map_y; i++)
	{
		for (int j = 0; j < map_x; j++)
		{
			if (game->map_section[i][j] != '1')
				draw_tile(game, game->mlx, game->win, j * (TILE_SIZE / 8), i * (TILE_SIZE / 8), (TILE_SIZE / 8), 0x000000);
			x += (TILE_SIZE / 8);
		}
		y += (TILE_SIZE / 8);
	}
	mlx_put_image_to_window(game->mlx, game->win, game->img, 0, 0);
}
