/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_section2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sodahani <sodahani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 16:48:35 by sodahani          #+#    #+#             */
/*   Updated: 2025/05/04 18:31:49 by sodahani         ###   ########.fr       */
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

