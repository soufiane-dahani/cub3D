/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbakour <zbakour@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 22:52:10 by zbakour           #+#    #+#             */
/*   Updated: 2025/06/23 19:23:26 by zbakour          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int is_move_valid(t_game *game, int new_x, int new_y)
{
	int size = TILE_SIZE / 4;
	int margin = 4;
	int map_width_px = game->map_width * TILE_SIZE;
	int map_height_px = game->map_height * TILE_SIZE;
	int left = new_x - margin;
	int right = new_x + size + margin;
	int top = new_y - margin;
	int bottom = new_y + size + margin;

	if (left < 0 || top < 0 || right >= map_width_px || bottom >= map_height_px)
		return 0;
	int tile_x1 = left / TILE_SIZE;
	int tile_y1 = top / TILE_SIZE;
	int tile_x2 = right / TILE_SIZE;
	int tile_y2 = bottom / TILE_SIZE;
	if (game->map_section[tile_y1][tile_x1] == '1' ||
			game->map_section[tile_y1][tile_x2] == '1' ||
			game->map_section[tile_y2][tile_x1] == '1' ||
			game->map_section[tile_y2][tile_x2] == '1')
		return (0);
	return (1);
}
