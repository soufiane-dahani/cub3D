/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doors.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sodahani <sodahani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 22:48:03 by sodahani          #+#    #+#             */
/*   Updated: 2025/08/24 11:55:42 by sodahani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

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

void	update_doors(t_game *game)
{
	int	i;

	i = 0;
	while (i < game->num_doors)
	{
		if (!game->doors[i].is_open)
			game->map_section[game->doors[i].x][game->doors[i].y] = 'D';
		else
			game->map_section[game->doors[i].x][game->doors[i].y] = 'O';
		i++;
	}
}

void	normalize_facing_vector(t_game *game, double *fx, double *fy)
{
	double	flen;

	*fx = game->pdx;
	*fy = game->pdy;
	flen = sqrt(*fx * *fx + *fy * *fy);
	if (flen > 0.000000001)
	{
		*fx /= flen;
		*fy /= flen;
	}
	else
	{
		*fx = cos(game->player_angle);
		*fy = sin(game->player_angle);
	}
}
