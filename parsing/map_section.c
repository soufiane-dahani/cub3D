/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_section.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sodahani <sodahani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 16:48:35 by sodahani          #+#    #+#             */
/*   Updated: 2025/05/04 15:35:12 by sodahani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static void	set_up_map(t_game *game)
{
	int	i;
	int	len;

	len = 0;
	while (game->map[game->map_start_index + len] != NULL)
		len++;
	while (len > 0 && is_empty_line(game->map[game->map_start_index + len - 1]))
		len--;
	i = 0;
	game->map_section = ft_malloc(sizeof(char *) * (len + 1), FT_ALLOC);
	while (i < len)
	{
		game->map_section[i] = ft_malloc(ft_strlen(game->map[game->map_start_index
					+ i]) + 1, FT_ALLOC);
		ft_strlcpy(game->map_section[i], game->map[game->map_start_index + i],
				ft_strlen(game->map[game->map_start_index + i]) + 1);
		i++;
	}
	game->map_section[i] = NULL;
}

static void	check_count(t_game *game)
{
	int		i;
	int		j;
	int		found;
	int		len;
	char	c;

	i = 0;
	found = 0;
	while (game->map_section[i] != NULL)
	{
		j = 0;
		len = ft_strlen(game->map_section[i]);
		if (len > game->max_len)
			game->max_len = len;
		while (game->map_section[i][j] != '\n')
		{
			c = game->map_section[i][j];
			if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
				found++;
			else if (c != '0' && c != '1' && c != ' ')
				handle_init_errors(4);
			j++;
		}
		i++;
	}
	if (found != 1)
		handle_init_errors(5);
}

static void	prepare_map(t_game *game)
{
	int		i;
	int		j;
	int		len;
	int		max_len;
	char	*new_line;

	i = 0;
	max_len = game->max_len;
	while (game->map_section[i] != NULL)
	{
		len = ft_strlen(game->map_section[i]);
		new_line = ft_malloc(sizeof(char) * (max_len + 1), FT_ALLOC);
		j = 0;
		while (j < len && game->map_section[i][j] != '\n')
		{
			if (game->map_section[i][j] == ' ')
				new_line[j] = 'X';
			else
				new_line[j] = game->map_section[i][j];
			j++;
		}
		while (j < max_len)
		{
			new_line[j] = 'X';
			j++;
		}
		new_line[j - 1] = '\n';
		new_line[j] = '\0';
		game->map_section[i] = new_line;
		i++;
	}
}

void	map_section(t_game *game)
{
	int	i;

	set_up_map(game);
	game->max_len = 0;
	check_count(game);
	prepare_map(game);
	i = 0;
	while (game->map_section[i] != NULL)
	{
		printf("%s", game->map_section[i]);
		i++;
	}
}
