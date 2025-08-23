/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sodahani <sodahani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/21 13:56:16 by zbakour           #+#    #+#             */
/*   Updated: 2025/08/23 13:54:49 by sodahani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

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
	//draw_map_bg(game);
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

void	raycasting(t_game *game)
{
	init_player(game);
	init_game_params(game);
	setup_hooks(game);
	mlx_loop(game->mlx);
}
