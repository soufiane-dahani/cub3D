/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_section3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sodahani <sodahani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 16:48:35 by sodahani          #+#    #+#             */
/*   Updated: 2025/08/25 08:45:50 by sodahani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static int	count_rows(char **map)
{
	int	i;

	i = 0;
	while (map[i])
		i++;
	return (i);
}

static char	*dup_and_replace(char *src)
{
	int		i;
	int		len;
	char	*dst;

	len = ft_strlen(src);
	dst = ft_malloc(sizeof(char) * (len + 1), FT_ALLOC);
	if (!dst)
		return (NULL);
	i = 0;
	while (src[i])
	{
		if (src[i] == 'X')
			dst[i] = '1';
		else
			dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (dst);
}

void	map_section3(t_game *game)
{
	int	rows;
	int	i;

	rows = count_rows(game->map_section);
	game->map_section2 = ft_malloc(sizeof(char *) * (rows + 1), FT_ALLOC);
	if (!game->map_section2)
		return ;
	i = 0;
	while (i < rows)
	{
		game->map_section2[i] = dup_and_replace(game->map_section[i]);
		if (!game->map_section2[i])
			return ;
		i++;
	}
	game->map_section2[i] = NULL;
}
