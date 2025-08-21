/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbakour <zbakour@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/21 13:57:52 by zbakour           #+#    #+#             */
/*   Updated: 2025/08/21 13:58:10 by zbakour          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	put_pixels(t_game *game, int x, int y, int color)
{
	char	*data;
	int		offset;
	int		bpp;
	int		line_length;
	int		endian;

	data = mlx_get_data_addr(game->img, &bpp, &line_length, &endian);
	if (x >= 0 && x <= SCREEN_WIDTH && y >= 0 && y <= SCREEN_HEIGHT)
	{
		offset = (y * line_length) + (x * (bpp / 8));
		*(unsigned int *)(data + offset) = color;
	}
}
