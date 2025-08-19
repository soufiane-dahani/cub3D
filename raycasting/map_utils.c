/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbakour <zbakour@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 22:49:02 by zbakour           #+#    #+#             */
/*   Updated: 2025/08/19 18:25:30 by zbakour          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	draw_background(t_game *game)
{
	int		bits_per_pixel;
	int		size_line;
	int		endian;
	char	*data;

	data = mlx_get_data_addr(game->img, &bits_per_pixel, &size_line, &endian);
	for (int y = 0; y < MAP_HEIGHT; y++)
		for (int x = 0; x < SCREEN_WIDTH; x++)
			put_pixel(data, x, y, 0x808080, size_line);
	mlx_put_image_to_window(game->mlx, game->win, game->img, 0, 0);
}

void	draw_player(t_game *game)
{
	int		player_w;
	int		px;
	int		py;

	player_w = (TILE_SIZE / 4) / 4;
	px = game->player_x / 8;
	py = game->player_y / 8;
	if (py > TILE_SIZE / 8 && py < MAP_HEIGHT)
		draw_tile(game, game->mlx, game->win, px, py, player_w / 2, 0xFF0000);
}

static	void draw_wall_or_door(t_game *game, int i, int j)
{
	if (game->map_section[i][j] == '1')
				draw_tile(game, game->mlx, game->win, j * (TILE_SIZE / 8), i
					* (TILE_SIZE / 8), (TILE_SIZE / 8), 0xFFFF00);
	else if (game->map_section[i][j] == 'D')
		draw_tile(game, game->mlx, game->win, j * (TILE_SIZE / 8), i
			* (TILE_SIZE / 8), (TILE_SIZE / 8), 0x00FF00);
}

void	draw_map_walls(t_game *game)
{
	int		x;
	int		y;
	int 	i;
	int 	j;

	x = 0;
	y = 0;
	i = 0;
	while (i < game->map_height)
	{
		j = 0;
		while ( j < game->map_width)
		{
			draw_wall_or_door(game, i, j);
			x += TILE_SIZE;
			j++;
		}
		y += TILE_SIZE;
		i++;
	}
	mlx_put_image_to_window(game->mlx, game->win, game->img, 0, 0);
}

void	draw_map_bg(t_game *game)
{
	int		x;
	int		y;
	int 	i;
	int		j;
	
	x = 0;
	y = 0;
	i = 0;
	while (i < game->map_height)
	{
		j = 0;
		while (j < game->map_width)
		{
			if (game->map_section[i][j] != '1')
				draw_tile(game, game->mlx, game->win, j * (TILE_SIZE / 8), i
					* (TILE_SIZE / 8), (TILE_SIZE / 8), game->ceiling);
			x += (TILE_SIZE / 8);
			j++;
		}
		y += (TILE_SIZE / 8);
		i++;
	}
	mlx_put_image_to_window(game->mlx, game->win, game->img, 0, 0);
}
