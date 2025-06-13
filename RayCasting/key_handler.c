/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_handler.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbakour <zbakour@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 22:52:30 by zbakour           #+#    #+#             */
/*   Updated: 2025/06/13 18:03:10 by zbakour          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	key_hook(int keycode, t_game *game)
{
	if (keycode == 65307)
		exit(0);
	else if (keycode == 100) // D (strafe right)
	{
		double strafe_angle = game->player_angle + M_PI_2;
		double new_x = game->player_x + cos(strafe_angle);
		double new_y = game->player_y + sin(strafe_angle);
		int new_tile_x = (int)(new_x / TILE_SIZE);
		int new_tile_y = (int)(new_y / TILE_SIZE);
		if (is_move_valid(game, new_x, new_y) && new_x < SCREEN_WIDTH - TILE_SIZE && game->map_section[new_tile_y][new_tile_x] != '1')
		{
			game->player_x = new_x;
			game->player_y = new_y;
			cast_rays(game);
		}
	}
	else if (keycode == 97) // A (strafe left)
	{
		double strafe_angle = game->player_angle - (M_PI / 2);
		double new_x = game->player_x + cos(strafe_angle) * 5;
		double new_y = game->player_y + sin(strafe_angle) * 5;
		int new_tile_x = (int)(new_x / TILE_SIZE);
		int new_tile_y = (int)(new_y / TILE_SIZE);
		if (is_move_valid(game, new_x, new_y) && new_x > TILE_SIZE && game->map_section[new_tile_y][new_tile_x] != '1')
		{
			game->player_x = new_x;
			game->player_y = new_y;
			cast_rays(game);
		}
	}
	else if (keycode == 119) // W
	{
		double new_x = game->player_x + game->pdx;
		double new_y = game->player_y + game->pdy;
		int new_tile_x = (int)(new_x / TILE_SIZE);
		int new_tile_y = (int)(new_y / TILE_SIZE);
		if (is_move_valid(game, new_x, new_y) && new_y > TILE_SIZE && game->map_section[new_tile_y][new_tile_x] != '1')
		{
			game->player_x = new_x;
			game->player_y = new_y;
			cast_rays(game);
		}
	}
	else if (keycode == 115) // S
	{
		double new_x = game->player_x - game->pdx;
		double new_y = game->player_y - game->pdy;
		int new_tile_x = (int)(new_x / TILE_SIZE);
		int new_tile_y = (int)(new_y / TILE_SIZE);
		if (is_move_valid(game, new_x, new_y) && new_y < MAP_HEIGHT - TILE_SIZE && game->map_section[new_tile_y][new_tile_x] != '1')
		{
			game->player_x = new_x;
			game->player_y = new_y;
			cast_rays(game);
		}
	}
	else if (keycode == 65363) // right arrow
	{
		game->player_angle += 0.1;
		normalize_angle(game->player_angle);
		game->pdx = cos(game->player_angle) * 5;
		game->pdy = sin(game->player_angle) * 5;
		cast_rays(game);
	}
	else if (keycode == 65361)
	{
		game->player_angle -= 0.1;
		normalize_angle(game->player_angle);
		game->pdx = cos(game->player_angle) * 5;
		game->pdy = sin(game->player_angle) * 5;
		cast_rays(game);
		
	}
	// printf("player ( x, y ): ( %f, %f )\n", game->player_x, game->player_y);
	return (0);
}