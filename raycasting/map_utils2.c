/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sodahani <sodahani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 16:48:35 by sodahani          #+#    #+#             */
/*   Updated: 2025/08/21 13:01:36 by sodahani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static void	draw_wall_or_door(t_game *game, int pos[4])
{
	if (pos[2] < 0 || pos[2] >= game->map_height || pos[3] < 0
		|| pos[3] >= game->map_width)
	{
		draw_tile(game, pos[1] * (TILE_SIZE / 8), pos[0] * (TILE_SIZE / 8),
			(TILE_SIZE / 8), 0x000000);
		return ;
	}
	if (game->map_section[pos[2]][pos[3]] == '1')
		draw_tile(game, pos[1] * (TILE_SIZE / 8), pos[0] * (TILE_SIZE / 8),
			(TILE_SIZE / 8), 0xFFFF00);
	else if (game->map_section[pos[2]][pos[3]] == 'D'
		|| game->map_section[pos[2]][pos[3]] == 'O')
		draw_tile(game, pos[1] * (TILE_SIZE / 8), pos[0] * (TILE_SIZE / 8),
			(TILE_SIZE / 8), 0x00FF00);
}

void	get_player_tile_pos(t_game *game, int *player_tile_x,
		int *player_tile_y)
{
	*player_tile_x = (game->player_x / 8) / (TILE_SIZE / 8);
	*player_tile_y = (game->player_y / 8) / (TILE_SIZE / 8);
}

static void	draw_wall_loop(t_game *game, int player_pos[2])
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
			draw_wall_or_door(game, pos);
			screen_coord[1]++;
		}
		screen_coord[0]++;
	}
}

void	draw_map_walls(t_game *game)
{
	int	player_pos[2];

	get_player_tile_pos(game, &player_pos[0], &player_pos[1]);
	draw_wall_loop(game, player_pos);
	mlx_put_image_to_window(game->mlx, game->win, game->img, 0, 0);
}
