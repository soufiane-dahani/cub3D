/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_handler.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sodahani <sodahani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 22:52:30 by zbakour           #+#    #+#             */
/*   Updated: 2025/08/17 18:50:12 by sodahani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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
		cast_rays(game);
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
		cast_rays(game);
	}
	else
	{
		if (is_move_valid(game, new_x, game->player_y))
		{
			game->player_x = new_x;
			cast_rays(game);
		}
		else if (is_move_valid(game, game->player_x, new_y))
		{
			game->player_y = new_y;
			cast_rays(game);
		}
	}
}

static void	handle_rotation(t_game *game, double rotation)
{
	game->player_angle += rotation;
	game->player_angle = normalize_angle(game->player_angle);
	game->pdx = cos(game->player_angle);
	game->pdy = sin(game->player_angle);
	cast_rays(game);
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
		ft_malloc(0, FT_CLEAR);
		exit(0);
	}
	else
		handle_movement_keys(keycode, game);
	return (0);
}
void render_animation(t_game *game)
{
    t_texture *frame = &game->anim_textures[game->anim.current_frame];
    int start_x = (SCREEN_WIDTH - frame->width) / 2;
    int start_y = MAP_HEIGHT - frame->height; // bottom of the screen

    for (int y = 0; y < frame->height; y++)
    {
        for (int x = 0; x < frame->width; x++)
        {
            int color = get_texture_color(frame, x, y);
            if ((color & 0x00FFFFFF) != 0) // skip transparent pixels
                put_pixels(game, start_x + x, start_y + y, color);
        }
    }
}
void update_animation(t_game *game)
{
    if (!game->anim.playing)
        return;

    game->anim.frame_counter+=5;
    if (game->anim.frame_counter >= game->anim.frame_delay)
    {
        game->anim.frame_counter = 0;
        game->anim.current_frame++;

        if (game->anim.current_frame > 3)
        {
            game->anim.current_frame = 0;
            game->anim.playing = 0;
        }
    }
}
