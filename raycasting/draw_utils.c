/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbakour <zbakour@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 18:44:18 by zbakour           #+#    #+#             */
/*   Updated: 2025/08/21 14:20:24 by zbakour          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	draw_line(t_game *game, t_line line)
{
	float	dx;
	float	dy;
	float	steps;
	int		i;

	dx = line.x1 - line.x0;
	dy = line.y1 - line.y0;
	if (fabs(dx) > fabs(dy))
		steps = fabs(dx);
	else
		steps = fabs(dy);
	i = 0;
	while (i <= steps)
	{
		put_pixels(game, (int)line.x0, (int)line.y0, line.color);
		line.x0 += dx / steps;
		line.y0 += dy / steps;
		i++;
	}
}

void	draw_vertical_line(t_game *game, t_line line)
{
	int	y;

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

static void	texture_line_render(t_game *game, t_texture_line *texture_line_data,
		t_ray_data *ray)
{
	int	y;
	int	color;

	y = ray->draw_start;
	while (y <= ray->draw_end)
	{
		ray->tex_y = (int)texture_line_data->tex_pos;
		if (ray->tex_y < 0)
			ray->tex_y = 0;
		if (ray->tex_y >= texture_line_data->texture->height)
			ray->tex_y = texture_line_data->texture->height - 1;
		color = get_texture_color(texture_line_data->texture,
				texture_line_data->tex_x, ray->tex_y);
		if (ray->side == 1)
			color = (color >> 1) & 0x7F7F7F;
		put_pixels(game, texture_line_data->col, y, color);
		texture_line_data->tex_pos += texture_line_data->step;
		y++;
	}
}

void	draw_textured_line(t_game *game, t_ray_data *ray, int col)
{
	t_texture_line	texture_line_data;

	texture_line_data.col = col;
	texture_line_data.texture = get_wall_texture(game, ray->side, ray->step_x,
			ray->step_y);
	texture_line_data.tex_x = (int)(ray->wall_x
			* texture_line_data.texture->width);
	if ((ray->side == 0 && ray->ray_dx > 0) || (ray->side == 1
			&& ray->ray_dy < 0))
		texture_line_data.tex_x = texture_line_data.texture->width
			- texture_line_data.tex_x - 1;
	if (texture_line_data.tex_x < 0)
		texture_line_data.tex_x = 0;
	if (texture_line_data.tex_x >= texture_line_data.texture->width)
		texture_line_data.tex_x = texture_line_data.texture->width - 1;
	texture_line_data.step = (double)texture_line_data.texture->height
		/ ray->wall_height;
	texture_line_data.tex_pos = (ray->draw_start - SCREEN_HEIGHT / 2
			+ ray->wall_height / 2) * texture_line_data.step;
	texture_line_render(game, &texture_line_data, ray);
}
