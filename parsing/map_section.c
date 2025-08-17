/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_section.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sodahani <sodahani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 16:48:35 by sodahani          #+#    #+#             */
/*   Updated: 2025/08/17 15:45:29 by sodahani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	validate_map_char(char c, t_game *game, int row, int col)
{
	if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
	{
		game->player_x = col + 1;
		game->player_y = row + 1;
		game->player_char = c;
		return (1);
	}
	else if (c != '0' && c != '1' && c != ' ' && c != 'D')
	{
		handle_init_errors(4);
	}
	return (0);
}

static void	check_count(t_game *game)
{
	int (row), (col), (player_count), (len);
	row = 0;
	player_count = 0;
	while (game->map_section[row] != NULL)
	{
		col = 0;
		len = ft_strlen(game->map_section[row]);
		if (len > game->max_len)
			game->max_len = len;
		while (game->map_section[row][col] && game->map_section[row][col]
			&& game->map_section[row][col] != '\n')
		{
			player_count += validate_map_char(game->map_section[row][col],
					game, row, col);
			col++;
		}
		if (col >= 32 || row > 33)
			handle_init_errors(5);
		row++;
	}
	if (player_count != 1)
		handle_init_errors(5);
}

static void	fill_new_line(char *new_line, char *old_line, int max_len)
{
	int	j;
	int	len;

	j = 0;
	len = ft_strlen(old_line);
	while (j < len && old_line[j] != '\n')
	{
		if (old_line[j] == ' ')
			new_line[j] = 'X';
		else
			new_line[j] = old_line[j];
		j++;
	}
	while (j < max_len)
	{
		new_line[j] = 'X';
		j++;
	}
	new_line[j - 1] = '\n';
	new_line[j] = '\0';
}

static void	prepare_map(t_game *game)
{
	int		i;
	int		max_len;
	char	*new_line;
	char	*copy_line;

	i = 0;
	max_len = game->max_len;
	while (game->map_section[i] != NULL)
	{
		new_line = ft_malloc(sizeof(char) * (max_len + 1), FT_ALLOC);
		fill_new_line(new_line, game->map_section[i], max_len);
		game->map_section[i] = new_line;
		copy_line = ft_malloc(sizeof(char) * (max_len + 1), FT_ALLOC);
		ft_strlcpy(copy_line, new_line, max_len + 1);
		game->map_copy[i] = copy_line;
		i++;
	}
	game->map_copy[i] = NULL;
}

void	map_section(t_game *game)
{
	set_up_map(game);
	game->max_len = 0;
	check_count(game);
	check_count_of_doors(game);
	prepare_map(game);
	flood_fill(game->map_copy, game->player_y, game->player_x);
	set_player_direction(game);
}
