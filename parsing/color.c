/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sodahani <sodahani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 16:48:35 by sodahani          #+#    #+#             */
/*   Updated: 2025/08/17 17:15:46 by sodahani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	get_color(int rgb[3])
{
	int	red;
	int	green;
	int	blue;

	red = rgb[0];
	green = rgb[1];
	blue = rgb[2];
	return (red << 16 | green << 8 | blue);
}

void	change_to_hex(t_game *game)
{
	game->floor = mlx_get_color_value(game->mlx, get_color(game->floor_color));
	game->ceiling = mlx_get_color_value(game->mlx,
			get_color(game->ceiling_color));
}
