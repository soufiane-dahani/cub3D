/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbakour <zbakour@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 22:49:02 by zbakour           #+#    #+#             */
/*   Updated: 2025/06/13 03:49:09 by zbakour          ###   ########.fr       */
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

void	draw_player(t_game *game)
{
    int red = 0xFF0000;
    int green = 0x00FF00;
    int bpp, line_length, endian;
    char *data = mlx_get_data_addr(game->img, &bpp, &line_length, &endian);

    int player_w = TILE_SIZE / 4;
    int player_h = TILE_SIZE / 4;
    int px = game->player_x;
    int py = game->player_y;

    // Draw player as a square
    if (py >  TILE_SIZE / 4 && py < MAP_HEIGHT)
    {
        draw_tile(game, game->mlx, game->win, px, py, player_w, red);

        // Draw direction line from the center of the player
        double angle = game->player_angle;
        int line_length_px = TILE_SIZE; // Length of the direction line

        int cx = px + player_w / 2;
        int cy = py + player_h / 2;
        int x2 = cx + cos(angle) * line_length_px;
        int y2 = cy + sin(angle) * line_length_px;

        // Simple Bresenham's line algorithm
        int dx = abs(x2 - cx), sx = cx < x2 ? 1 : -1;
        int dy = -abs(y2 - cy), sy = cy < y2 ? 1 : -1;
        int err = dx + dy, e2;

        int x = cx, y = cy;
        while (1)
        {
            put_pixel(data, x, y, red, line_length);
            if (x == x2 && y == y2) break;
            e2 = 2 * err;
            if (e2 >= dy) { err += dy; x += sx; }
            if (e2 <= dx) { err += dx; y += sy; }
        }

        mlx_put_image_to_window(game->mlx, game->win, game->img, 0, 0);
    }
}

void	draw_map(t_game *game)
{
	int yellow = 0xFFFF00;
	int bpp, line_length, endian;
    char *data = mlx_get_data_addr(game->img, &bpp, &line_length, &endian);

	draw_background(game);
	int map_x = 16;
	int map_y = 8;
	int x = 0;
	int y = 0;
	for (int i = 0; i < map_y; i++)
	{
		for (int j = 0; j < map_x; j++)
		{
			if (game->map_section[i][j] == '1')
    			draw_tile(game, game->mlx, game->win, j * TILE_SIZE,  i * TILE_SIZE, TILE_SIZE, yellow);
			else
				draw_tile(game, game->mlx, game->win, j * TILE_SIZE,  i * TILE_SIZE, TILE_SIZE , 0x000000);
			x+= TILE_SIZE - 16;
		}
		y+= TILE_SIZE - 16;
	}
	mlx_put_image_to_window(game->mlx, game->win, game->img, 0, 0);
}