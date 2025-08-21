/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sodahani <sodahani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 22:49:02 by zbakour           #+#    #+#             */
/*   Updated: 2025/08/21 13:02:00 by sodahani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	draw_background(t_game *game)
{
	int		bits_per_pixel;
	int		size_line;
	int		endian;
	char	*data;
	int		coord[2];

	data = mlx_get_data_addr(game->img, &bits_per_pixel, &size_line, &endian);
	coord[1] = 0;
	while (coord[1] < SCREEN_HEIGHT)
	{
		coord[0] = 0;
		while (coord[0] < SCREEN_WIDTH)
		{
			put_pixel(data, coord[0], coord[1], 0x808080, size_line);
			coord[0]++;
		}
		coord[1]++;
	}
	mlx_put_image_to_window(game->mlx, game->win, game->img, 0, 0);
}

void	draw_player(t_game *game)
{
	int	player_w;
	int	px;
	int	py;

	player_w = (TILE_SIZE / 4) / 4;
	px = 5 * (TILE_SIZE / 8);
	py = 5 * (TILE_SIZE / 8);
	if (py > TILE_SIZE / 8 && py < SCREEN_HEIGHT)
		draw_tile(game, px, py, player_w / 2, 0xFF0000);
}

static void	draw_bg_tile(t_game *game, int pos[4])
{
	if (pos[2] >= 0 && pos[2] < game->map_height && pos[3] >= 0
		&& pos[3] < game->map_width)
	{
		if (game->map_section[pos[2]][pos[3]] != '1')
			draw_tile(game, pos[1] * (TILE_SIZE / 8), pos[0] * (TILE_SIZE / 8),
				(TILE_SIZE / 8), game->ceiling);
	}
	else
	{
		draw_tile(game, pos[1] * (TILE_SIZE / 8), pos[0] * (TILE_SIZE / 8),
			(TILE_SIZE / 8), 0x000000);
	}
}

static void	draw_bg_loop(t_game *game, int player_pos[2])
{
	int	screen_coord[2];
	int	pos[4];

	screen_coord[0] = 0;
	while (screen_coord[0] < 11)
	{
		screen_coord[1] = 0;
		while (screen_coord[1] < 11)
		{
			pos[0] = screen_coord[0];
			pos[1] = screen_coord[1];
			pos[2] = player_pos[1] - 5 + screen_coord[0];
			pos[3] = player_pos[0] - 5 + screen_coord[1];
			draw_bg_tile(game, pos);
			screen_coord[1]++;
		}
		screen_coord[0]++;
	}
}

void	draw_map_bg(t_game *game)
{
	int	player_pos[2];

	get_player_tile_pos(game, &player_pos[0], &player_pos[1]);
	draw_bg_loop(game, player_pos);
	mlx_put_image_to_window(game->mlx, game->win, game->img, 0, 0);
}
