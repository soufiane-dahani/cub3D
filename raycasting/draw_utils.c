/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbakour <zbakour@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 18:44:18 by zbakour           #+#    #+#             */
/*   Updated: 2025/08/19 19:59:39 by zbakour          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	draw_line(t_game *game, t_line line)
{
	float	dx;
	float	dy;
	float	steps;
	float	x_inc;
	float	y_inc;
	float	x;
	float	y;
	int		i;

	dx = line.x1 - line.x0;
	dy = line.y1 - line.y0;
	if (fabs(dx) > fabs(dy))
		steps = fabs(dx);
	else
		steps = fabs(dy);
	x_inc = dx / steps;
	y_inc = dy / steps;
	x = line.x0;
	y = line.y0;
	i = 0;
	while (i <= steps)
	{
		put_pixels(game, (int)x, (int)y, line.color);
		x += x_inc;
		y += y_inc;
		i++;
	}
}

void	draw_vertical_line(t_game *game, t_line line)
{
	int y;

	y = line.y0;
	while (y <= line.y1)
	{
		if (line.x0 >= 0 && line.x0 < SCREEN_WIDTH && y >= 0 
			&& y < SCREEN_HEIGHT)
			put_pixels(game, line.x0, y, line.color);
		y++;
	}
}

void	draw_background_2(t_game *game)
{
	int	x;
	int	y;

	y = 0;
	while (y < SCREEN_HEIGHT / 2)
	{
		x = 0;
		while (x < SCREEN_WIDTH)
		{
			put_pixels(game, x, y, game->ceiling);
			x++;
		}
		y++;
	}
	y = SCREEN_HEIGHT / 2;
	while (y < SCREEN_HEIGHT)
	{
		x = 0;
		while (x < SCREEN_WIDTH)
		{
			put_pixels(game, x, y, game->floor);
			x++;
		}
		y++;
	}
}

void	draw_textured_line(t_game *game, t_ray_data *ray, int col)
{
	t_texture	*texture;
	int			tex_x;
	double		step;
	double		tex_pos;
	int			y;
	int			color;

	texture = get_wall_texture(game, ray->side, ray->step_x, ray->step_y);
	tex_x = (int)(ray->wall_x * texture->width);
	if ((ray->side == 0 && ray->ray_dx > 0)
		|| (ray->side == 1 && ray->ray_dy < 0))
		tex_x = texture->width - tex_x - 1;
	if (tex_x < 0)
		tex_x = 0;
	if (tex_x >= texture->width)
		tex_x = texture->width - 1;
	step = (double)texture->height / ray->wall_height;
	tex_pos = (ray->draw_start - SCREEN_HEIGHT / 2 + ray->wall_height / 2)
		* step;
	y = ray->draw_start;
	while (y <= ray->draw_end)
	{
		ray->tex_y = (int)tex_pos;
		if (ray->tex_y < 0)
			ray->tex_y = 0;
		if (ray->tex_y >= texture->height)
			ray->tex_y = texture->height - 1;
		color = get_texture_color(texture, tex_x, ray->tex_y);
		if (ray->side == 1)
			color = (color >> 1) & 0x7F7F7F;
		put_pixels(game, col, y, color);
		tex_pos += step;
		y++;
	}
}
