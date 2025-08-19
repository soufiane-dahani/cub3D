/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_helpers.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbakour <zbakour@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 18:44:18 by zbakour           #+#    #+#             */
/*   Updated: 2025/08/19 19:59:39 by zbakour          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	init_ray_vars(t_ray_data *ray, double ray_angle, t_game *game)
{
	ray->ray_dx = cos(ray_angle);
	ray->ray_dy = sin(ray_angle);
	ray->map_x = game->player_x / TILE_SIZE;
	ray->map_y = game->player_y / TILE_SIZE;
	ray->map_x_int = (int)ray->map_x;
	ray->map_y_int = (int)ray->map_y;
	if (ray->ray_dx == 0)
		ray->delta_dist_x = 1e30;
	else
		ray->delta_dist_x = fabs(1 / ray->ray_dx);
	if (ray->ray_dy == 0)
		ray->delta_dist_y = 1e30;
	else
		ray->delta_dist_y = fabs(1 / ray->ray_dy);
	ray->hit = false;
	ray->is_door = false;
}

void	calc_step_and_side_dist(t_ray_data *ray)
{
	if (ray->ray_dx < 0)
	{
		ray->step_x = -1;
		ray->side_dist_x = (ray->map_x - ray->map_x_int) * ray->delta_dist_x;
	}
	else
	{
		ray->step_x = 1;
		ray->side_dist_x = (ray->map_x_int + 1.0 - ray->map_x)
			* ray->delta_dist_x;
	}
	if (ray->ray_dy < 0)
	{
		ray->step_y = -1;
		ray->side_dist_y = (ray->map_y - ray->map_y_int) * ray->delta_dist_y;
	}
	else
	{
		ray->step_y = 1;
		ray->side_dist_y = (ray->map_y_int + 1.0 - ray->map_y)
			* ray->delta_dist_y;
	}
}

void	perform_dda(t_ray_data *ray, t_game *game)
{
	while (!ray->hit)
	{
		if (ray->side_dist_x < ray->side_dist_y)
		{
			ray->side_dist_x += ray->delta_dist_x;
			ray->map_x_int += ray->step_x;
			ray->side = 0;
		}
		else
		{
			ray->side_dist_y += ray->delta_dist_y;
			ray->map_y_int += ray->step_y;
			ray->side = 1;
		}
		if (ray->map_x_int < 0 || ray->map_x_int >= game->map_width
			|| ray->map_y_int < 0 || ray->map_y_int >= game->map_height)
			return ;
		if (game->map_section[ray->map_y_int][ray->map_x_int] == '1')
			ray->hit = true;
		else if (game->map_section[ray->map_y_int][ray->map_x_int] == 'D')
		{
			ray->is_door = true;
			ray->hit = true;
		}
	}
}

void	calc_distance_and_wall_x(t_ray_data *ray)
{
	if (ray->side == 0)
	{
		ray->distance = (ray->map_x_int - ray->map_x
				+ (1 - ray->step_x) / 2) / ray->ray_dx;
		ray->wall_x = ray->map_y + ray->distance * ray->ray_dy;
		ray->wall_x = ray->wall_x - floor(ray->wall_x);
	}
	else
	{
		ray->distance = (ray->map_y_int - ray->map_y
				+ (1 - ray->step_y) / 2) / ray->ray_dy;
		ray->wall_x = ray->map_x + ray->distance * ray->ray_dx;
		ray->wall_x = ray->wall_x - floor(ray->wall_x);
	}
	if (ray->is_door)
		ray->side = -99;
	ray->distance *= TILE_SIZE;
}
