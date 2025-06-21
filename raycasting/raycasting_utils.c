/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbakour <zbakour@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 21:24:32 by zbakour           #+#    #+#             */
/*   Updated: 2025/06/21 17:27:47 by zbakour          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void define_player_angle(t_game *game)
{
    if (game->player_char == 'N')
        game->player_angle = M_PI / 2;
    else if (game->player_char == 'S')
        game->player_angle = 3 * M_PI / 2;
    else if (game->player_char == 'E')
        game->player_angle = 0;
    else if (game->player_char == 'W')
        game->player_angle = M_PI;
}

double normalize_angle(double angle)
{
	while (angle < 0)
		angle += 2 * M_PI;
	while (angle >= 2 * M_PI)
		angle -= 2 * M_PI;
	return angle;
}