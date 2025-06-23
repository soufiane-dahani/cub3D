/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbakour <zbakour@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 22:52:10 by zbakour           #+#    #+#             */
/*   Updated: 2025/06/23 16:30:08 by zbakour          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int is_move_valid(t_game *game, int new_x, int new_y)
{
	int size = TILE_SIZE / 4; // 16

	// Check map boundaries
	if (new_x < 0 || new_y < 0 || new_x + size >= (SCREEN_WIDTH * TILE_SIZE) || new_y + size >= (MAP_HEIGHT * TILE_SIZE))
		return (0);
	if (game->map_section[new_y / TILE_SIZE][new_x / TILE_SIZE] == '1' ||
			game->map_section[new_y / TILE_SIZE][(new_x + size) / TILE_SIZE] == '1' ||
			game->map_section[(new_y + size) / TILE_SIZE][new_x / TILE_SIZE] == '1' ||
			game->map_section[(new_y + size) / TILE_SIZE][(new_x + size) / TILE_SIZE] == '1')
		return (0);

	return (1);
}
