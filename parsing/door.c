/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sodahani <sodahani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 16:48:35 by sodahani          #+#    #+#             */
/*   Updated: 2025/08/24 11:23:05 by sodahani         ###   ########.fr       */
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

void	check_top_row(char **map)
{
	int	j;
	int	len;

	len = ft_strlen(map[0]);
	len--;
	len--;
	j = 0;
	while (map[0][j] == 'X')
		j++;
	while (map[0][len] == 'X')
		len--;
	while (j <= len)
	{
		if (map[0][j] != '1')
			handle_init_errors(6);
		j++;
	}
}

void	check_middle_rows(char **map)
{
	int	i;
	int	j;
	int	len;

	i = 1;
	while (map[i] != NULL)
	{
		len = ft_strlen(map[i]);
		j = 0;
		while (map[i][j] == 'X')
			j++;
		len--;
		len--;
		while (map[i][len] == 'X')
			len--;
		if (map[i][len] != '1' || map[i][j] != '1')
			handle_init_errors(6);
		i++;
	}
}

void	check_bottom_row(char **map, int i)
{
	int	j;
	int	len;

	i--;
	len = ft_strlen(map[i]);
	j = 0;
	while (map[i][j] == 'X')
		j++;
	len--;
	len--;
	while (map[i][len] == 'X')
		len--;
	while (j < len + 1)
	{
		if (map[i][j] != '1')
			handle_init_errors(6);
		j++;
	}
}

void	is_map_surrounded(t_game *game)
{
	int	i;

	check_top_row(game->map_section);
	check_middle_rows(game->map_section);
	i = 0;
	while (game->map_section[i] != NULL)
		i++;
	check_bottom_row(game->map_section, i);
}
