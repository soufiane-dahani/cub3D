/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sodahani <sodahani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 22:48:03 by obarais           #+#    #+#             */
/*   Updated: 2025/08/18 10:05:35 by sodahani         ###   ########.fr       */
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

	int bpp, line_length, endian;
	data = mlx_get_data_addr(game->img, &bpp, &line_length, &endian);
	if (x >= 0 && x <= SCREEN_WIDTH && y >= 0 && y <= MAP_HEIGHT)
	{
		offset = (y * line_length) + (x * (bpp / 8));
		*(unsigned int *)(data + offset) = color;
	}
}

void	draw_line(t_game *game, int x0, int y0, int x1, int y1, int color)
{
	float	dx;
	float	dy;
	float	steps;
	float	x_inc;
	float	y_inc;
	float	x;
	float	y;

	dx = x1 - x0;
	dy = y1 - y0;
	steps = fabs(dx) > fabs(dy) ? fabs(dx) : fabs(dy);
	x_inc = dx / steps;
	y_inc = dy / steps;
	x = x0;
	y = y0;
	for (int i = 0; i <= steps; i++)
	{
		put_pixels(game, (int)x, (int)y, color);
		x += x_inc;
		y += y_inc;
	}
}

void	draw_vertical_line(t_game *game, int x, int y_start, int y_end,
		int color)
{
	for (int y = y_start; y <= y_end; y++)
	{
		if (x >= 0 && x < SCREEN_WIDTH && y >= 0 && y < MAP_HEIGHT)
			put_pixels(game, x, y, color);
	}
}

void	draw_background_2(t_game *game)
{

	int x, y;
	for (y = 0; y < MAP_HEIGHT / 2; y++)
	{
		for (x = 0; x < SCREEN_WIDTH; x++)
			put_pixels(game, x, y, game->ceiling);
	}
	for (y = MAP_HEIGHT / 2; y < MAP_HEIGHT; y++)
	{
		for (x = 0; x < SCREEN_WIDTH; x++)
			put_pixels(game, x, y, game->floor);
	}
}

void	cast_ray(t_game *game, double ray_angle, int i)
{
	double		ray_dx;
	double		ray_dy;
	double		map_x;
	double		map_y;
	int			map_x_int;
	int			map_y_int;
	double		delta_dist_x;
	double		delta_dist_y;
	bool		hit;
	double		distance;
	double		screen_distance;
	double		wall_height;
	int			draw_start;
	int			draw_end;
	t_texture	*texture;
	int			tex_x;
	double		step;
	double		tex_pos;
	int			tex_y;
	int			color;

	ray_dx = cos(ray_angle);
	ray_dy = sin(ray_angle);
	// Player's position in map coordinates
	map_x = game->player_x / TILE_SIZE;
	map_y = game->player_y / TILE_SIZE;
	// Which box of the map we're in
	map_x_int = (int)map_x;
	map_y_int = (int)map_y;
	// Length of ray to next x or y side
	delta_dist_x = (ray_dx == 0) ? 1e30 : fabs(1 / ray_dx);
	delta_dist_y = (ray_dy == 0) ? 1e30 : fabs(1 / ray_dy);
	// Step and initial side distance
	int step_x, step_y;
	double side_dist_x, side_dist_y;
	// Calculate step and initial side_dist_x
	if (ray_dx < 0)
	{
		step_x = -1;
		side_dist_x = (map_x - map_x_int) * delta_dist_x;
	}
	else
	{
		step_x = 1;
		side_dist_x = (map_x_int + 1.0 - map_x) * delta_dist_x;
	}
	if (ray_dy < 0)
	{
		step_y = -1;
		side_dist_y = (map_y - map_y_int) * delta_dist_y;
	}
	else
	{
		step_y = 1;
		side_dist_y = (map_y_int + 1.0 - map_y) * delta_dist_y;
	}
	// Perform DDA
	hit = false;
	int side; // 0 = vertical wall, 1 = horizontal wall
	while (!hit)
	{
		// Jump to next map square, either in x-direction, or in y-direction
		if (side_dist_x < side_dist_y)
		{
			side_dist_x += delta_dist_x;
			map_x_int += step_x;
			side = 0;
		}
		else
		{
			side_dist_y += delta_dist_y;
			map_y_int += step_y;
			side = 1;
		}
		// Check if ray has hit a wall
		if (map_x_int < 0 || map_x_int >= game->map_width || map_y_int < 0
			|| map_y_int >= game->map_height)
			return ; // Hit boundary
		if (game->map_section[map_y_int][map_x_int] == '1')
			hit = true;
	}
	// Calculate distance to wall
	double wall_x; // Calculate texture coordinate before distance conversion
	if (side == 0) // Vertical wall
	{
		distance = (map_x_int - map_x + (1 - step_x) / 2) / ray_dx;
		// For vertical walls, texture coordinate comes from Y position
		wall_x = map_y + distance * ray_dy;
		wall_x = wall_x - floor(wall_x);
	}
	else // Horizontal wall
	{
		distance = (map_y_int - map_y + (1 - step_y) / 2) / ray_dy;
		// For horizontal walls, texture coordinate comes from X position
		wall_x = map_x + distance * ray_dx;
		wall_x = wall_x - floor(wall_x);
	}
	// Convert back to pixel coordinates
	distance *= TILE_SIZE;
	// Fish-eye fix
	distance *= cos(ray_angle - game->player_angle);
	screen_distance = SCREEN_WIDTH / (2.0 * tan(game->fov / 2.0));
	wall_height = (TILE_SIZE * screen_distance) / distance;
	draw_start = (MAP_HEIGHT / 2) - (wall_height / 2);
	draw_end = (MAP_HEIGHT / 2) + (wall_height / 2);
	// Clamp to screen bounds
	if (draw_start < 0)
		draw_start = 0;
	if (draw_end >= MAP_HEIGHT)
		draw_end = MAP_HEIGHT - 1;
	// Get the appropriate texture
	texture = get_wall_texture(game, side, step_x, step_y);
	// Calculate texture x coordinate
	tex_x = (int)(wall_x * texture->width);
	if ((side == 0 && ray_dx > 0) || (side == 1 && ray_dy < 0))
		tex_x = texture->width - tex_x - 1;
	// Ensure tex_x is within bounds
	if (tex_x < 0)
		tex_x = 0;
	if (tex_x >= texture->width)
		tex_x = texture->width - 1;
	// Calculate texture step and starting position
	step = (double)texture->height / wall_height;
	tex_pos = (draw_start - MAP_HEIGHT / 2 + wall_height / 2) * step;
	// Draw textured vertical line
	for (int y = draw_start; y <= draw_end; y++)
	{
		tex_y = (int)tex_pos;
		if (tex_y < 0)
			tex_y = 0;
		if (tex_y >= texture->height)
			tex_y = texture->height - 1;
		color = get_texture_color(texture, tex_x, tex_y);
		// Apply some shading based on wall side for depth effect
		if (side == 1)
			color = (color >> 1) & 0x7F7F7F; // Darken horizontal walls
		put_pixels(game, i, y, color);
		tex_pos += step;
	}
}

void	cast_rays(t_game *game)
{
	// static long	last_update = 0;
	// long		now;
	double		angle_step;
	double		ray_angle;

	// now = current_millis();
	// if (now - last_update < 16)
	// 	return ;
	// draw_background(game);
	update_animation(game);
	draw_background_2(game);
	angle_step = game->fov / game->num_rays;
	draw_map_bg(game);
	game->start_angle = game->player_angle - (game->fov / 2);
	for (int i = 0; i < game->num_rays; i++)
	{
		ray_angle = game->start_angle + (i * angle_step);
		ray_angle = normalize_angle(ray_angle);
		cast_ray(game, ray_angle, i);
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
	// double		angle_step;
	// double		ray_angle;

	game = (t_game *)param;
	now = current_millis();
	if (now - last_update < 80)
		return (1);
	last_update = now;
	cast_rays(game);
	return (0);
}


void raycasting(t_game *game)
{
    calculate_tile_position(game);
    define_player_angle(game);
    game->player_x = (game->player_x * TILE_SIZE) + 16 + (16 / 2);
    game->player_y = (game->player_y * TILE_SIZE) + 16 + (16 / 2);

    draw_map(game);
    draw_player(game);

    game->fov = M_PI / 3;
    game->player_angle = normalize_angle(game->player_angle);
    game->pdx = cos(game->player_angle);
    game->pdy = sin(game->player_angle);
    game->start_angle = normalize_angle(game->player_angle - (game->fov / 2));
    game->end_angle = normalize_angle(game->player_angle + (game->fov / 2));
    game->num_rays = SCREEN_WIDTH;

    load_textures(game);
    cast_rays(game);

    mlx_hook(game->win, 2, 1L << 0, key_hook, game);
    mlx_mouse_hide(game->mlx, game->win);
    mlx_mouse_move(game->mlx, game->win, SCREEN_WIDTH / 2, MAP_HEIGHT / 2);
    mlx_hook(game->win, 6, 1L << 6, mouse_hook, game);

    mlx_hook(game->win, 17, 0, close_window, game); // safe close

    mlx_loop_hook(game->mlx, render_next_frame, game);

    mlx_loop(game->mlx);
}

