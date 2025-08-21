/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sodahani <sodahani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 22:49:26 by zbakour           #+#    #+#             */
/*   Updated: 2025/08/21 16:45:36 by sodahani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	my_mlx_pixel_put(t_texture *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_len + x * (data->bpp / 8));
	*(unsigned int *)dst = color;
}

void	draw_tile(t_game *game, t_texture *texture)
{
	int	i;
	int	j;

	texture->addr = mlx_get_data_addr(game->img, &texture->bpp,
			&texture->line_len, &texture->endian);
	i = 0;
	while (i < texture->size)
	{
		j = 0;
		while (j < texture->size)
		{
			my_mlx_pixel_put(texture, texture->x + j, texture->y + i,
				texture->color);
			j++;
		}
		i++;
	}
}

void	calculate_tile_position(t_game *game)
{
	int	i;
	int	j;
	int	max;

	max = 0;
	i = 0;
	while (game->map_section[i])
	{
		j = 0;
		while (game->map_section[i][j])
			j++;
		if (max < j)
			max = j;
		i++;
	}
	game->map_width = max - 1;
	game->map_height = i;
}
