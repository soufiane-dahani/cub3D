/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doors.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sodahani <sodahani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 22:48:03 by sodahani          #+#    #+#             */
/*   Updated: 2025/08/17 15:36:28 by sodahani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	check_count_of_doors(t_game *game)
{
	int	row;
	int	col;

	game->num_doors = 0;
	row = 0;
	while (game->map_section[row] != NULL)
	{
		col = 0;
		while (game->map_section[row][col] && game->map_section[row][col]
			&& game->map_section[row][col] != '\n')
		{
			if (game->map_section[row][col] == 'D')
				game->num_doors++;
			col++;
		}
		row++;
	}
	if (game->num_doors > 4)
		handle_init_errors(6);
}

void	init_doors(t_game *game)
{
	int	row;
	int	col;
	int	door_index;

	row = 0;
	door_index = 0;
	while (game->map_section[row] != NULL)
	{
		col = 0;
		while (game->map_section[row][col] != '\n')
		{
			if (game->map_section[row][col] == 'D')
			{
				add_door(game, row, col, door_index);
				door_index++;
			}
			col++;
		}
		row++;
	}
}

void	add_door(t_game *game, int x, int y, int index)
{
	t_door	*door;

	door = &game->doors[index];
	door->x = x;
	door->y = y;
	door->is_open = 0;
}

void	try_open_doors(t_game *game)
{
	int	px;
	int	py;
	int	i;
	int	dx;
	int	dy;

	px = (int)game->player_x;
	py = (int)game->player_y;
	i = 0;
	while (i < game->num_doors)
	{
		dx = game->doors[i].x;
		dy = game->doors[i].y;
		if (abs(dx - px) + abs(dy - py) == 1)
		{
			game->doors[i].is_open = !game->doors[i].is_open;
			break ;
		}
		i++;
	}
}

int	is_door_open(t_game *game, int x, int y)
{
	int	i;

	i = 0;
	while (i < game->num_doors)
	{
		if (game->doors[i].x == x && game->doors[i].y == y)
			return (game->doors[i].is_open);
		i++;
	}
	return (0);
}
