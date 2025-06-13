/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbakour <zbakour@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 22:52:10 by zbakour           #+#    #+#             */
/*   Updated: 2025/06/13 03:58:21 by zbakour          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// int	is_move_valid(t_game *game, int new_x, int new_y)
// {
// 	if (new_x < 0 || new_y < 0 || new_x + 16 >= (15 * TILE_SIZE)
// 		|| (new_y >= (8 * TILE_SIZE) - 16))
// 		return (0);
// 	if (game->map_section[new_y / 64][new_x / 64] == '1')
// 		return (0);
// 	return (1);
// }

int	is_move_valid(t_game *game, int new_x, int new_y)
{
	int px = new_x;
	int py = new_y;
	int size = TILE_SIZE / 4; // 16

	// Check map boundaries
	if (px < 0 || py < 0 || px + size >= (SCREEN_WIDTH * TILE_SIZE)
		|| py + size >= (MAP_HEIGHT * TILE_SIZE))
		return (0);

	// Check all 4 corners of the player's box
	if (game->map_section[py / TILE_SIZE][px / TILE_SIZE] == '1' || // top-left
		game->map_section[py / TILE_SIZE][(px + size ) / TILE_SIZE] == '1' || // top-right
		game->map_section[(py + size ) / TILE_SIZE][px / TILE_SIZE] == '1' || // bottom-left
		game->map_section[(py + size ) / TILE_SIZE][(px + size ) / TILE_SIZE] == '1') // bottom-right
		return (0);

	return (1);
}
