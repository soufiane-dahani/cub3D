/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sodahani <sodahani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 22:52:10 by zbakour           #+#    #+#             */
/*   Updated: 2025/08/18 10:04:22 by sodahani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	is_move_valid(t_game *game, int new_x, int new_y)
{
	int	size;
	int	margin;
	int	map_width_px;
	int	map_height_px;
	int	left;
	int	right;
	int	top;
	int	bottom;
	int	tile_x1;
	int	tile_y1;
	int	tile_x2;
	int	tile_y2;

	size = TILE_SIZE / 8;
	margin = 8;
	map_width_px = game->map_width * TILE_SIZE;
	map_height_px = game->map_height * TILE_SIZE;
	left = new_x - margin;
	right = new_x + size + margin;
	top = new_y - margin;
	bottom = new_y + size + margin;
	if (left < 0 || top < 0 || right >= map_width_px || bottom >= map_height_px)
		return (0);
	tile_x1 = left / TILE_SIZE;
	tile_y1 = top / TILE_SIZE;
	tile_x2 = right / TILE_SIZE;
	tile_y2 = bottom / TILE_SIZE;
	if (game->map_section[tile_y1][tile_x1] == '1'
		|| game->map_section[tile_y1][tile_x2] == '1'
		|| game->map_section[tile_y2][tile_x1] == '1'
		|| game->map_section[tile_y2][tile_x2] == '1')
		return (0);
	return (1);
}
