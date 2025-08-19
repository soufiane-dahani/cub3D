/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sodahani <sodahani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 22:48:03 by obarais           #+#    #+#             */
/*   Updated: 2025/08/19 20:52:37 by sodahani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

long	current_millis(void)
{
	struct timeval	t;

	gettimeofday(&t, NULL);
	return (t.tv_sec * 1000 + t.tv_usec / 1000);
}

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

void	cast_ray(t_game *game, double ray_angle, int i)
{
	t_ray_data	ray;

	init_ray_vars(&ray, ray_angle, game);
	calc_step_and_side_dist(&ray);
	perform_dda(&ray, game);
	if (!ray.hit)
		return ;
	calc_distance_and_wall_x(&ray);
	ray.distance *= cos(ray_angle - game->player_angle);
	ray.screen_distance = SCREEN_WIDTH / (2.0 * tan(game->fov / 2.0));
	ray.wall_height = (TILE_SIZE * ray.screen_distance) / ray.distance;
	ray.draw_start = (SCREEN_HEIGHT / 2) - (ray.wall_height / 2);
	ray.draw_end = (SCREEN_HEIGHT / 2) + (ray.wall_height / 2);
	if (ray.draw_start < 0)
		ray.draw_start = 0;
	if (ray.draw_end >= SCREEN_HEIGHT)
		ray.draw_end = SCREEN_HEIGHT - 1;
	draw_textured_line(game, &ray, i);
}

void	cast_rays(t_game *game)
{
	double	angle_step;
	double	ray_angle;
	int		i;

	draw_background_2(game);
	angle_step = game->fov / game->num_rays;
	draw_map_bg(game);
	game->start_angle = game->player_angle - (game->fov / 2);
	i = 0;
	while (i < game->num_rays)
	{
		ray_angle = game->start_angle + (i * angle_step);
		ray_angle = normalize_angle(ray_angle);
		cast_ray(game, ray_angle, i);
		i++;
	}
	draw_map_walls(game);
	draw_player(game);
	render_animation(game);
	mlx_put_image_to_window(game->mlx, game->win, game->img, 0, 0);
}

int	render_next_frame(void *param)
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

static void	init_player(t_game *game)
{
	calculate_tile_position(game);
	define_player_angle(game);
	game->player_x = (game->player_x * TILE_SIZE) - TILE_SIZE / 2;
	game->player_y = (game->player_y * TILE_SIZE) - TILE_SIZE / 2;
	draw_player(game);
}

static void	init_game_params(t_game *game)
{
	game->fov = M_PI / 3;
	game->player_angle = normalize_angle(game->player_angle);
	game->pdx = cos(game->player_angle);
	game->pdy = sin(game->player_angle);
	game->start_angle = normalize_angle(game->player_angle - (game->fov / 2));
	game->end_angle = normalize_angle(game->player_angle + (game->fov / 2));
	game->num_rays = SCREEN_WIDTH;
	load_textures(game);
}

static void	setup_hooks(t_game *game)
{
	mlx_hook(game->win, 2, 1L << 0, key_hook, game);
	mlx_mouse_hide(game->mlx, game->win);
	mlx_mouse_move(game->mlx, game->win, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
	mlx_hook(game->win, 6, 1L << 6, mouse_hook, game);
	mlx_hook(game->win, 17, 0, close_window, game);
	mlx_loop_hook(game->mlx, render_next_frame, game);
}

void	raycasting(t_game *game)
{
	init_player(game);
	init_game_params(game);
	setup_hooks(game);
	mlx_loop(game->mlx);
}
