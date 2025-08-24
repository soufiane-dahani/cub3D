/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doors_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sodahani <sodahani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 22:48:03 by sodahani          #+#    #+#             */
/*   Updated: 2025/08/23 18:50:14 by sodahani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static int	is_door_adjacent_and_front(t_game *game, int i, double fx,
		double fy)
{
	int	pxi;
	int	pyi;
	int	dx;
	int	dy;

	pxi = (int)(game->player_x / TILE_SIZE);
	pyi = (int)(game->player_y / TILE_SIZE);
	dx = game->doors[i].y - pxi;
	dy = game->doors[i].x - pyi;
	if (abs(dx) + abs(dy) != 1)
		return (0);
	return (dx * fx + dy * fy > 0);
}

static double	calculate_door_dot(t_game *game, int i, double fx, double fy)
{
	int	pxi;
	int	pyi;
	int	dx;
	int	dy;

	pxi = (int)(game->player_x / TILE_SIZE);
	pyi = (int)(game->player_y / TILE_SIZE);
	dx = game->doors[i].y - pxi;
	dy = game->doors[i].x - pyi;
	return (dx * fx + dy * fy);
}

static int	find_best_door(t_game *game, double fx, double fy)
{
	int		best_idx;
	double	best_dot;
	int		i;
	double	dot;

	best_idx = -1;
	best_dot = 0.0;
	i = 0;
	while (i < game->num_doors)
	{
		if (is_door_adjacent_and_front(game, i, fx, fy))
		{
			dot = calculate_door_dot(game, i, fx, fy);
			if (dot > best_dot)
			{
				best_dot = dot;
				best_idx = i;
			}
		}
		i++;
	}
	return (best_idx);
}

void	try_open_doors(t_game *game)
{
	double	fx;
	double	fy;
	int		best_idx;

	normalize_facing_vector(game, &fx, &fy);
	best_idx = find_best_door(game, fx, fy);
	if (best_idx != -1)
	{
		game->doors[best_idx].is_open = !game->doors[best_idx].is_open;
		update_doors(game);
	}
}
