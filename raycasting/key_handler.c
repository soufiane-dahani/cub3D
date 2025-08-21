/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_handler.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sodahani <sodahani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 22:52:30 by zbakour           #+#    #+#             */
/*   Updated: 2025/08/20 17:41:43 by sodahani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static void	handle_strafe_movement(t_game *game, double direction)
{
	double	strafe_angle;
	double	new_x;
	double	new_y;

	strafe_angle = game->player_angle + direction;
	new_x = game->player_x + cos(strafe_angle) * MOVE_SPEED;
	new_y = game->player_y + sin(strafe_angle) * MOVE_SPEED;
	if (is_move_valid(game, new_x, new_y))
	{
		game->player_x = new_x;
		game->player_y = new_y;
	}
	else
	{
		if (is_move_valid(game, new_x, game->player_y))
			game->player_x = new_x;
		else if (is_move_valid(game, game->player_x, new_y))
			game->player_y = new_y;
	}
}

static void	handle_forward_backward(t_game *game, int direction)
{
	double	new_x;
	double	new_y;

	new_x = game->player_x + game->pdx * MOVE_SPEED * direction;
	new_y = game->player_y + game->pdy * MOVE_SPEED * direction;
	if (is_move_valid(game, new_x, new_y))
	{
		game->player_x = new_x;
		game->player_y = new_y;
	}
	else
	{
		if (is_move_valid(game, new_x, game->player_y))
			game->player_x = new_x;
		else if (is_move_valid(game, game->player_x, new_y))
			game->player_y = new_y;
		else
		{
			if (is_move_valid(game, new_x - 20, game->player_y))
				game->player_x = new_x - 20;
			else if (is_move_valid(game, game->player_x, new_y - 20))
				game->player_y = new_y - 20;
		}
	}
}

static void	handle_rotation(t_game *game, double rotation)
{
	game->player_angle += rotation;
	game->player_angle = normalize_angle(game->player_angle);
	game->pdx = cos(game->player_angle);
	game->pdy = sin(game->player_angle);
}

static void	handle_movement_keys(int keycode, t_game *game)
{
	if (keycode == D_KEY)
		handle_strafe_movement(game, M_PI_2);
	else if (keycode == A_KEY)
		handle_strafe_movement(game, -M_PI_2);
	else if (keycode == W_KEY)
		handle_forward_backward(game, 1);
	else if (keycode == S_KEY)
		handle_forward_backward(game, -1);
	else if (keycode == RIGHT_ARROW)
		handle_rotation(game, ROTATION_SPEED);
	else if (keycode == LEFT_ARROW)
		handle_rotation(game, -ROTATION_SPEED);
	else if (keycode == SPACE_KEY && !game->anim.playing)
	{
		game->anim.playing = 1;
		game->anim.current_frame = 1;
		game->anim.frame_counter = 0;
	}
}

int	key_hook(int keycode, t_game *game)
{
	if (keycode == ESC_KEY)
	{
		cleanup_game(game);
		exit(0);
	}
	else if(keycode == F_KEY )
		try_open_doors(game);
	else
		handle_movement_keys(keycode, game);
	return (0);
}
