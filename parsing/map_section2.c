/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_section2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sodahani <sodahani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 16:48:35 by sodahani          #+#    #+#             */
/*   Updated: 2025/05/04 20:05:32 by sodahani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	set_up_map(t_game *game)
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
	game->map_copy = ft_malloc(sizeof(char *) * (len + 1), FT_ALLOC);
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

void	flood_fill(char **map, int y, int x)
{
	char	c;

	if (y < 0 || x < 0 || map[y] == NULL || x >= (int)ft_strlen(map[y]))
		handle_init_errors(6);
	c = map[y][x];
	if (c == '1' || c == 'V')
		return ;
	else if (c == 'X' || c == '\0')
		handle_init_errors(6);
	else if (c == '0' || c == 'N' || c == 'S' || c == 'E' || c == 'W')
		map[y][x] = 'V';
	flood_fill(map, y - 1, x);
	flood_fill(map, y + 1, x);
	flood_fill(map, y, x - 1);
	flood_fill(map, y, x + 1);
}
void	set_player_direction_vector(t_game *game)
{
	if (game->player_char == 'N')
	{
		game->dir_x = 0;
		game->dir_y = -1;
	}
	else if (game->player_char == 'S')
	{
		game->dir_x = 0;
		game->dir_y = 1;
	}
	else if (game->player_char == 'E')
	{
		game->dir_x = 1;
		game->dir_y = 0;
	}
	else if (game->player_char == 'W')
	{
		game->dir_x = -1;
		game->dir_y = 0;
	}
}

void	set_player_camera_plane(t_game *game)
{
	if (game->player_char == 'N')
	{
		game->plane_x = 0.66;
		game->plane_y = 0;
	}
	else if (game->player_char == 'S')
	{
		game->plane_x = -0.66;
		game->plane_y = 0;
	}
	else if (game->player_char == 'E')
	{
		game->plane_x = 0;
		game->plane_y = 0.66;
	}
	else if (game->player_char == 'W')
	{
		game->plane_x = 0;
		game->plane_y = -0.66;
	}
}

void	set_player_direction(t_game *game)
{
	set_player_direction_vector(game);
	set_player_camera_plane(game);
}
