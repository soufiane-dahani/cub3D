/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sodahani <sodahani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 16:48:35 by sodahani          #+#    #+#             */
/*   Updated: 2025/08/23 15:35:52 by sodahani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	is_valid_door(t_game *game)
{
	int	row;
	int	col;

	row = 0;
	while (game->map_section[row] != NULL)
	{
		col = 0;
		while (game->map_section[row][col])
		{
			if (game->map_section[row][col] == 'D')
			{
				if (game->map_section[row][col - 1] == '1'
					&& game->map_section[row][col + 1] == '1')
					;
				else if (game->map_section[row - 1][col] == '1'
						&& game->map_section[row + 1][col] == '1')
					;
				else
					handle_init_errors(8);
			}
			col++;
		}
		row++;
	}
	return (1);
}
