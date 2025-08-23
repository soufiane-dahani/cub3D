/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbakour <zbakour@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/21 13:58:51 by zbakour           #+#    #+#             */
/*   Updated: 2025/08/23 15:52:34 by zbakour          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	init_player(t_game *game)
{
	calculate_tile_position(game);
	define_player_angle(game);
	game->player_x = (game->player_x * TILE_SIZE) - TILE_SIZE / 2;
	game->player_y = (game->player_y * TILE_SIZE) - TILE_SIZE / 2;
	draw_player(game);
}

void	init_game_params(t_game *game)
{
	game->fov = M_PI / 3;
	game->player_angle = normalize_angle(game->player_angle);
	game->pdx = cos(game->player_angle);
	game->pdy = sin(game->player_angle);
	game->start_angle = normalize_angle(game->player_angle - (game->fov / 2));
	game->num_rays = SCREEN_WIDTH;
	load_textures(game);
}

static int	render_next_frame(void *param)
{
	t_game		*game;
	static long	last_update = 0;
	long		now;

	game = (t_game *)param;
	now = current_millis();
	if (now - last_update < 80)
		return (1);
	last_update = now;
	cast_rays(game);
	update_animation(game);
	return (0);
}

void	setup_hooks(t_game *game)
{
	mlx_hook(game->win, 2, 1L << 0, key_hook, game);
	mlx_mouse_hide(game->mlx, game->win);
	mlx_mouse_move(game->mlx, game->win, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
	mlx_hook(game->win, 6, 1L << 6, mouse_hook, game);
	mlx_hook(game->win, 17, 0, close_window, game);
	mlx_loop_hook(game->mlx, render_next_frame, game);
}
