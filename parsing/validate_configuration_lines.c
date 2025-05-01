/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_configuration_lines.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sodahani <sodahani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 16:48:35 by sodahani          #+#    #+#             */
/*   Updated: 2025/05/01 23:41:16 by sodahani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static void	handle_texture_line(char *line, char **texture, int *count)
{
	*texture = extract_path(line);
	(*count)++;
}

static void	handle_color_line(char *line, t_game *game, int type, int *count)
{
	extract_number(line, game, type);
	(*count)++;
}

static void	process_config_line(t_game *game, int *config_count, char *line)
{
	if (!ft_strncmp(line, "NO ", 3))
		handle_texture_line(line, &game->north_texture, config_count);
	else if (!ft_strncmp(line, "SO ", 3))
		handle_texture_line(line, &game->south_texture, config_count);
	else if (!ft_strncmp(line, "WE ", 3))
		handle_texture_line(line, &game->west_texture, config_count);
	else if (!ft_strncmp(line, "EA ", 3))
		handle_texture_line(line, &game->east_texture, config_count);
	else if (!ft_strncmp(line, "F ", 2))
		handle_color_line(line, game, 1, config_count);
	else if (!ft_strncmp(line, "C ", 2))
		handle_color_line(line, game, 2, config_count);
	else
	{
		ft_putstr_fd("Error: \nInvalid config line\n", 2);
		ft_malloc(0, FT_CLEAR);
		exit(1);
	}
}

int	is_empty_line(char *str)
{
	if (str[0] == '\0')
		return (1);
	else
		return (0);
}

void	validate_configuration_lines(t_game *game)
{
	int	config_count;
	int	i;

	config_count = 0;
	i = 0;
	while (config_count < 6 && game->map[i])
	{
		if (is_empty_line(game->map[i]))
		{
			i++;
			continue ;
		}
		process_config_line(game, &config_count, game->map[i]);
		i++;
	}
}
