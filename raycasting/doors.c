/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doors.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sodahani <sodahani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 22:48:03 by sodahani           #+#    #+#             */
/*   Updated: 2025/08/05 20:30:14 by sodahani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	check_count_of_doors(t_game *game)
{
	game->num_doors = 0;
	int row;
	int col;
	row = 0;
	while (game->map_section[row] != NULL)
	{
		col = 0;
		while (game->map_section[row][col] != '\n')
		{
			if (game->map_section[row][col] == 'D')
				game->num_doors++;
			col++;
		}
	}
}

void	init_doors(t_game *game)
{
	int row;
	int col;
	row = 0;
	while (game->map_section[row] != NULL)
	{
		col = 0;
		while (game->map_section[row][col] != '\n')
		{
			if (game->map_section[row][col] == 'D')
				add_door(game, row, col);
			col++;
		}
	}
}

void add_door(t_game *game, int x, int y)
{
	t_door *door = &game->doors[game->num_doors];

	door->x = x;
	door->y = y;
	door->is_open = 0; // closed by default
	door->timer = 0.0;
	game->num_doors++;
}

void try_open_doors(t_game *game)
{
	int px = (int)game->player_x;
	int py = (int)game->player_y;
	int i;
	int dx;
	int dy;
	i = 0;

	while (i < game->num_doors)
	{
		dx = game->doors[i].x;
		dy = game->doors[i].y;

		if (abs(dx - px) + abs(dy - py) == 1)
		{
			if (game->doors[i].timer <= 0)
			{
				game->doors[i].is_open = !game->doors[i].is_open;
				game->doors[i].timer = 0.3;
			}
			break;
		}
		i++;
	}
}
