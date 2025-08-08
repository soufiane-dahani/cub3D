/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbakour <zbakour@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 22:48:03 by obarais           #+#    #+#             */
/*   Updated: 2025/08/08 17:25:30 by zbakour          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void put_pixels(t_game *game, int x, int y, int color)
{
	int bpp, line_length, endian;
	char *data = mlx_get_data_addr(game->img, &bpp, &line_length, &endian);
	if (x >= 0 && x <= SCREEN_WIDTH && y >= 0 && y <= MAP_HEIGHT)
	{
		int offset = (y * line_length) + (x * (bpp / 8));
		*(unsigned int *)(data + offset) = color;
	}
}

void draw_line(t_game *game, int x0, int y0, int x1, int y1, int color)
{
	float dx = x1 - x0;
	float dy = y1 - y0;
	float steps = fabs(dx) > fabs(dy) ? fabs(dx) : fabs(dy);
	float x_inc = dx / steps;
	float y_inc = dy / steps;

	float x = x0;
	float y = y0;

	for (int i = 0; i <= steps; i++)
	{
		put_pixels(game, (int)x, (int)y, color);

		x += x_inc;
		y += y_inc;
	}
}

void draw_vertical_line(t_game *game, int x, int y_start, int y_end, int color)
{
	for (int y = y_start; y <= y_end; y++)
	{
		if (x >= 0 && x < SCREEN_WIDTH && y >= 0 && y < MAP_HEIGHT)
			put_pixels(game, x, y, color);
	}
}

void draw_background_2(t_game *game)
{
	int x, y;
	int floor_color = 0x222222;
	int ceiling_color = 0x444444;

	for (y = 0; y < MAP_HEIGHT / 2; y++)
	{
		for (x = 0; x < SCREEN_WIDTH; x++)
			put_pixels(game, x, y, ceiling_color);
	}
	for (y = MAP_HEIGHT / 2; y < MAP_HEIGHT; y++)
	{
		for (x = 0; x < SCREEN_WIDTH; x++)
			put_pixels(game, x, y, floor_color);
	}
}

void cast_ray(t_game *game, double ray_angle, int i)
{
	double ray_dx = cos(ray_angle);
	double ray_dy = sin(ray_angle);

	// Player's position in map coordinates
	double map_x = game->player_x / TILE_SIZE;
	double map_y = game->player_y / TILE_SIZE;

	// Which box of the map we're in
	int map_x_int = (int)map_x;
	int map_y_int = (int)map_y;

	// Length of ray to next x or y side
	double delta_dist_x = (ray_dx == 0) ? 1e30 : fabs(1 / ray_dx);
	double delta_dist_y = (ray_dy == 0) ? 1e30 : fabs(1 / ray_dy);

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
	bool hit = false;
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
		if (map_x_int < 0 || map_x_int >= game->map_width ||
			map_y_int < 0 || map_y_int >= game->map_height)
			return; // Hit boundary

		if (game->map_section[map_y_int][map_x_int] == '1')
			hit = true;
	}

	// Calculate distance to wall
	double distance;
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

	double screen_distance = SCREEN_WIDTH / (2.0 * tan(game->fov / 2.0));
	double wall_height = (TILE_SIZE * screen_distance) / distance;

	int draw_start = (MAP_HEIGHT / 2) - (wall_height / 2);
	int draw_end = (MAP_HEIGHT / 2) + (wall_height / 2);

	// Clamp to screen bounds
	if (draw_start < 0)
		draw_start = 0;
	if (draw_end >= MAP_HEIGHT)
		draw_end = MAP_HEIGHT - 1;

	// Get the appropriate texture
	t_texture *texture = get_wall_texture(game, side, step_x, step_y);

	// Calculate texture x coordinate
	int tex_x = (int)(wall_x * texture->width);
	if ((side == 0 && ray_dx > 0) || (side == 1 && ray_dy < 0))
		tex_x = texture->width - tex_x - 1;

	// Ensure tex_x is within bounds
	if (tex_x < 0)
		tex_x = 0;
	if (tex_x >= texture->width)
		tex_x = texture->width - 1;

	// Calculate texture step and starting position
	double step = (double)texture->height / wall_height;
	double tex_pos = (draw_start - MAP_HEIGHT / 2 + wall_height / 2) * step;

	// Draw textured vertical line
	for (int y = draw_start; y <= draw_end; y++)
	{
		int tex_y = (int)tex_pos;
		if (tex_y < 0)
			tex_y = 0;
		if (tex_y >= texture->height)
			tex_y = texture->height - 1;

		int color = get_texture_color(texture, tex_x, tex_y);

		// Apply some shading based on wall side for depth effect
		if (side == 1)
			color = (color >> 1) & 0x7F7F7F; // Darken horizontal walls

		put_pixels(game, i, y, color);
		tex_pos += step;
	}

	// Draw ray on minimap (scaled down)
	double end_x = game->player_x + distance * ray_dx;
	double end_y = game->player_y + distance * ray_dy;
	draw_line(game, ((int)(game->player_x + (TILE_SIZE / 4) / 2) / 4),
			  ((int)(game->player_y + (TILE_SIZE / 4) / 2)) / 4,
			  (int)end_x / 4, (int)end_y / 4, 0xFF0000);
}

void cast_rays(t_game *game)
{
	static long last_update = 0;
	long now = current_millis();
	if (now - last_update < 16)
		return;
	// draw_background(game);
	draw_background_2(game);
	double angle_step = game->fov / game->num_rays;
	draw_map_bg(game);
	game->start_angle = game->player_angle - (game->fov / 2);
	for (int i = 0; i < game->num_rays; i++)
	{
		// double ray_angle = normalize_angle(game->start_angle + (i * angle_step)) + game->player_angle;
		double ray_angle = game->start_angle + (i * angle_step);
		ray_angle = normalize_angle(ray_angle);
		cast_ray(game, ray_angle, i);
	}
	draw_map_walls(game);
	draw_player(game);
	mlx_put_image_to_window(game->mlx, game->win, game->img, 0, 0);
}

void rotate_vector(double *px, double *py, double angle)
{
	double old_x;
	double cos_a;
	double sin_a;

	old_x = *px;
	cos_a = cos(angle);
	sin_a = sin(angle);
	*px = old_x * cos_a - *py * sin_a;
	*py = old_x * sin_a + *py * cos_a;
}

long current_millis()
{
	struct timeval t;
	gettimeofday(&t, NULL);
	return t.tv_sec * 1000 + t.tv_usec / 1000;
}

int mouse_hook(int x, int y, void *param)
{
	t_game *game = (t_game *)param;
	static long last_update = 0;
	static int last_x = SCREEN_WIDTH / 2;
	long now = current_millis();

	// Confine mouse to window boundaries
	int confined_x = x;
	int confined_y = y;
	int moved_mouse = 0;

	if (x < 0)
	{
		confined_x = 0;
		moved_mouse = 1;
	}
	else if (x >= SCREEN_WIDTH)
	{
		confined_x = SCREEN_WIDTH - 1;
		moved_mouse = 1;
	}

	if (y < 0)
	{
		confined_y = 0;
		moved_mouse = 1;
	}
	else if (y >= MAP_HEIGHT)
	{
		confined_y = MAP_HEIGHT - 1;
		moved_mouse = 1;
	}

	// Move mouse back to boundaries if it went outside
	if (moved_mouse)
	{
		mlx_mouse_move(game->mlx, game->win, confined_x, confined_y);
		return (0);
	}

	int delta_x = confined_x - last_x;

	if (delta_x != 0 && (now - last_update > 16)) // ~60 FPS
	{
		double sensitivity = 0.015;
		double angle = delta_x * sensitivity;

		game->player_angle += angle;
		game->player_angle = normalize_angle(game->player_angle);
		game->pdx = cos(game->player_angle);
		game->pdy = sin(game->player_angle);

		cast_rays(game);
		last_update = now;
	}

	last_x = confined_x;
	return (0);
}

void raycasting(t_game *game)
{
	printf("player_x: %f\n", game->player_x);
	printf("player_y: %f\n", game->player_y);
	calculate_tile_position(game);
	define_player_angle(game);
	game->player_x = (game->player_x * TILE_SIZE) + 16 + (16 / 2);
	game->player_y = (game->player_y * TILE_SIZE) + 16 + (16 / 2);
	init_window(game);

	draw_map(game);
	draw_player(game);

	printf("Player char: %c | Angle: %f\n", game->player_char, game->player_angle);

	// printf("player_char: %c\n", game->player_char);

	// printf("dir_x: %f\n", game->dir_x);
	// printf("dir_y: %f\n", game->dir_y);
	// printf("plane_x: %f\n", game->plane_x);
	// printf("plane_y: %f\n", game->plane_y);

	game->fov = M_PI / 3; // 60 degrees
	game->player_angle = normalize_angle(game->player_angle);
	game->pdx = cos(game->player_angle); // Player delta x: The distance the ray has to travel to cross one square on the map in the X or Y direction.
	game->pdy = sin(game->player_angle); // Player delta y
	game->start_angle = normalize_angle(game->player_angle - (game->fov / 2));
	game->end_angle = normalize_angle(game->player_angle + (game->fov / 2));
	game->num_rays = SCREEN_WIDTH;
	// printf("Player FOV Range: (%.6f, %.6f)\n", game->end_angle, game->start_angle);
	// printf("Player FOV: (%f, %f)\n", game->start_angle, game->end_angle);
	// printf("Player angle: %f\n", game->player_angle);
	// printf("Number of rays: %d\n", game->num_rays);
	load_textures(game);

	cast_rays(game);

	mlx_hook(game->win, 2, 1L << 0, key_hook, game);
	// mlx_loop_hook(game->mlx, loop_hook, game);
	mlx_mouse_hide(game->mlx, game->win);

	// Position mouse at center of window initially
	mlx_mouse_move(game->mlx, game->win, SCREEN_WIDTH / 2, MAP_HEIGHT / 2);

	mlx_hook(game->win, 6, 1L << 6, mouse_hook, game);
	mlx_loop_hook(game->mlx, key_hook, game);

	mlx_hook(game->win, 17, 0, mlx_loop_end, game->mlx);
	// mlx_mouse_hook(game->win, mouse_hook, game);
	mlx_loop(game->mlx);
}
