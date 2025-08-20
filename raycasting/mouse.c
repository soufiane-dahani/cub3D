/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sodahani <sodahani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 22:48:03 by sodahani          #+#    #+#             */
/*   Updated: 2025/08/20 16:02:30 by sodahani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static int	reset_mouse_position(t_game *game, int *last_x, int *last_y)
{
	int	center_x;
	int	center_y;

	center_x = SCREEN_WIDTH / 2;
	center_y = SCREEN_HEIGHT / 2;
	mlx_mouse_move(game->mlx, game->win, center_x, center_y);
	*last_x = center_x;
	*last_y = center_y;
	return (0);
}

static void	update_player_angle(t_game *game, int delta_x)
{
	game->player_angle += delta_x * MOUSE_SENSITIVITY;
	game->player_angle = normalize_angle(game->player_angle);
	game->pdx = cos(game->player_angle);
	game->pdy = sin(game->player_angle);
	cast_rays(game);
}

static int	check_mouse_bounds(int x, int y, int margin)
{
	if (x < margin || x >= SCREEN_WIDTH - margin)
		return (1);
	if (y < margin || y >= SCREEN_HEIGHT - margin)
		return (1);
	return (0);
}

static int	should_throttle(long now, long last_update)
{
	if (now - last_update < 16)
		return (1);
	return (0);
}

int	mouse_hook(int x, int y, void *param)
{
	t_game		*game;
	static int	last_x = SCREEN_WIDTH / 2;
	static int	last_y = SCREEN_HEIGHT / 2;
	static long	last_update = 0;

	game = (t_game *)param;
	if (should_throttle(current_millis(), last_update))
		return (1);
	if (check_mouse_bounds(x, y, 50))
		return (reset_mouse_position(game, &last_x, &last_y));
	if ((x - last_x) != 0)
	{
		last_update = current_millis();
		update_player_angle(game, x - last_x);
	}
	last_x = x;
	last_y = y;
	return (0);
}
