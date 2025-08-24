/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sodahani <sodahani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 22:49:02 by zbakour           #+#    #+#             */
/*   Updated: 2025/08/24 16:31:19 by sodahani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	draw_background(t_game *game)
{
	int			coord[2];
	t_texture	texture;

	texture.addr = mlx_get_data_addr(game->img, &texture.bpp, &texture.size,
			&texture.line_len);
	coord[1] = 0;
	while (coord[1] < SCREEN_HEIGHT)
	{
		coord[0] = 0;
		while (coord[0] < SCREEN_WIDTH)
		{
			my_mlx_pixel_put(&texture, coord[0], coord[1], 0x808080);
			coord[0]++;
		}
		coord[1]++;
	}
	mlx_put_image_to_window(game->mlx, game->win, game->img, 0, 0);
}

void	draw_player(t_game *game)
{
	int			player_w;
	int			px;
	int			py;
	t_texture	texture;

	player_w = (TILE_SIZE / 4) / 4;
	px = 5 * (TILE_SIZE / 8) + (int)fmod((game->player_x / 8), 4);
	py = 5 * (TILE_SIZE / 8) + (int)fmod((game->player_y / 8), 4);
	if (py > TILE_SIZE / 8 && py < SCREEN_HEIGHT)
	{
		texture.x = px;
		texture.y = py;
		texture.size = player_w / 2;
		texture.color = 0xFF0000;
		draw_tile(game, &texture);
	}
}

static void	draw_bg_tile(t_game *game, int pos[4])
{
	t_texture	texture;

	texture.x = pos[1] * (TILE_SIZE / 8);
	texture.y = pos[0] * (TILE_SIZE / 8);
	texture.size = TILE_SIZE / 8;
	if (pos[2] >= 0 && pos[2] < game->map_height && pos[3] >= 0
		&& pos[3] < game->map_width)
	{
		if (game->map_section[pos[2]][pos[3]] != '1')
		{
			texture.color = game->ceiling;
			draw_tile(game, &texture);
		}
	}
	else
	{
		texture.color = 0x000000;
		draw_tile(game, &texture);
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
}
