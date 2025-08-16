/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbakour <zbakour@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 22:49:26 by zbakour           #+#    #+#             */
/*   Updated: 2025/08/05 18:06:44 by zbakour          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	put_pixel(char *data, int x, int y, int color, int line_length)
{
	int	offset;

	offset = y * line_length + x * 4;
	data[offset + 0] = color & 0xFF;         // Blue
	data[offset + 1] = (color >> 8) & 0xFF;  // Green
	data[offset + 2] = (color >> 16) & 0xFF; // Red
}

void	draw_tile(t_game *game, void *mlx, void *win, int x, int y, int size,
		int color)
{
	char	*data;

	int bpp, line_length, endian;
	data = mlx_get_data_addr(game->img, &bpp, &line_length, &endian);
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
			put_pixel(data, x + i, y + j, color, line_length);
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
		{
			j++;
		}
		if (max < j)
			max = j;
		i++;
	}
	game->map_width = max - 1;
	game->map_height = i;
}
