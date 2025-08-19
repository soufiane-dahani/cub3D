/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbakour <zbakour@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 22:52:10 by zbakour           #+#    #+#             */
/*   Updated: 2025/08/19 20:12:35 by zbakour          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static int	is_tile_blocked(t_game *game, int tile_x, int tile_y)
{
	char	tile;

	tile = game->map_section[tile_y][tile_x];
	return (tile == '1' || tile == 'D');
}

static int	check_boundaries(t_game *game, t_bounds bounds)
{
	int	map_width_px;
	int	map_height_px;

	map_width_px = game->map_width * TILE_SIZE;
	map_height_px = game->map_height * TILE_SIZE;
	if (bounds.left < 0 || bounds.top < 0 || bounds.right >= map_width_px
		|| bounds.bottom >= map_height_px)
		return (0);
	return (1);
}

static int	check_tile_collisions(t_game *game, t_bounds bounds)
{
	int	tile_x1;
	int	tile_y1;
	int	tile_x2;
	int	tile_y2;

	tile_x1 = bounds.left / TILE_SIZE;
	tile_y1 = bounds.top / TILE_SIZE;
	tile_x2 = bounds.right / TILE_SIZE;
	tile_y2 = bounds.bottom / TILE_SIZE;
	if (is_tile_blocked(game, tile_x1, tile_y1) || is_tile_blocked(game,
			tile_x2, tile_y1) || is_tile_blocked(game, tile_x1, tile_y2)
		|| is_tile_blocked(game, tile_x2, tile_y2))
		return (0);
	return (1);
}

int	is_move_valid(t_game *game, int new_x, int new_y)
{
	int			size;
	int			margin;
	t_bounds	bounds;

	size = TILE_SIZE / 8;
	margin = 8;
	bounds.left = new_x - margin;
	bounds.right = new_x + size + margin;
	bounds.top = new_y - margin;
	bounds.bottom = new_y + size + margin;
	if (!check_boundaries(game, bounds))
		return (0);
	return (check_tile_collisions(game, bounds));
}
