/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_handler.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbakour <zbakour@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 22:52:30 by zbakour           #+#    #+#             */
/*   Updated: 2025/08/05 17:02:33 by zbakour          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"


int key_hook(int keycode, t_game *game)
{
	if (keycode == 65307)
	{
		ft_malloc(0, FT_CLEAR);
		exit(0);
	}
	else if (keycode == 100) // D
	{
		double strafe_angle = game->player_angle + M_PI_2;
		double new_x = game->player_x + cos(strafe_angle) * 5;
		double new_y = game->player_y + sin(strafe_angle) * 5;
		if (is_move_valid(game, new_x, new_y))
		{
			game->player_x = new_x;
			game->player_y = new_y;
			cast_rays(game);
		}
	}
	else if (keycode == 97) // A
	{
		double strafe_angle = game->player_angle - M_PI_2;
		double new_x = game->player_x + cos(strafe_angle) * 5;
		double new_y = game->player_y + sin(strafe_angle) * 5;
		if (is_move_valid(game, new_x, new_y))
		{
			game->player_x = new_x;
			game->player_y = new_y;
			cast_rays(game);
		}
	}
	else if (keycode == 119) // W
	{
		double new_x = game->player_x + game->pdx * 5;
		double new_y = game->player_y + game->pdy * 5;
		if (is_move_valid(game, new_x, new_y))
		{
			game->player_x = new_x;
			game->player_y = new_y;
			cast_rays(game);
		}
	}
	else if (keycode == 115) // S
	{
		double new_x = game->player_x - game->pdx * 5;
		double new_y = game->player_y - game->pdy * 5;
		if (is_move_valid(game, new_x, new_y))
		{
			game->player_x = new_x;
			game->player_y = new_y;
			cast_rays(game);
		}
	}
	else if (keycode == 65363) // Right Arrow
	{
		game->player_angle += 0.05;
		game->player_angle = normalize_angle(game->player_angle);
		game->pdx = cos(game->player_angle);
		game->pdy = sin(game->player_angle);
		cast_rays(game);
	}
	else if (keycode == 65361) // Left Arrow
	{
		game->player_angle -= 0.05;
		game->player_angle = normalize_angle(game->player_angle);
		game->pdx = cos(game->player_angle);
		game->pdy = sin(game->player_angle);
		cast_rays(game);
	}
	return (0);
}
