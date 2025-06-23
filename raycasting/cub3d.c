/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbakour <zbakour@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 22:48:03 by obarais           #+#    #+#             */
/*   Updated: 2025/06/23 18:51:33 by zbakour          ###   ########.fr       */
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
	// Ray starting position (player center in pixels)
	double ray_x = game->player_x;
	double ray_y = game->player_y;

	// Ray direction
	double ray_dx = cos(ray_angle);
	double ray_dy = sin(ray_angle);

	// Step until wall or out of bounds (simple DDA)
	int dof = 0;
	while (dof < 30)
	{
		int map_x = (int)(ray_x / TILE_SIZE);
		int map_y = (int)(ray_y / TILE_SIZE);
		if (map_x < 0)
			map_x = (ray_x - 0.0001) / TILE_SIZE;
		if (map_y < 0)
			map_y = (ray_y - 0.0001) / TILE_SIZE;

		if (map_x < 0 || map_x >= game->map_width || map_y < 0 || map_y >= game->map_height)
			break;
		if (game->map_section[map_y][map_x] == '1')
			break;
		else
		{
			double step_size = 0.1;
			ray_x += ray_dx * step_size;
			ray_y += ray_dy * step_size;
			continue;
		}
		dof++;
	}
	double dx = ray_x - game->player_x;
	double dy = ray_y - game->player_y;
	double distance = sqrt(dx * dx + dy * dy);

	// Fish-eye fix
	distance *= cos(ray_angle - game->player_angle);
	double screen_distance = SCREEN_WIDTH / (2.0 * tan(game->fov / 2.0));
	double wall_height = (TILE_SIZE * screen_distance) / distance;

	int draw_start = (MAP_HEIGHT / 2) - (wall_height / 2);
	int draw_end = (MAP_HEIGHT / 2) + (wall_height / 2);
	int color = 0x7FFFD4;
	draw_vertical_line(game, i, draw_start, draw_end, color);
	// draw_line(game, (int)(game->player_x + (TILE_SIZE / 4) / 2), (int)(game->player_y + (TILE_SIZE / 4) / 2), (int)ray_x, (int)ray_y, 0xFF0000);
	draw_line(game, ((int)(game->player_x + (TILE_SIZE / 4) / 2) / 4), ((int)(game->player_y + (TILE_SIZE / 4) / 2)) / 4, (int)ray_x / 4, (int)ray_y / 4, 0xFF0000);
}

void cast_rays(t_game *game)
{
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

void raycasting(t_game *game)
{

	game->player_angle = 0.0;
	calculate_tile_position(game);
	define_player_angle(game);
	game->player_x = game->player_x * TILE_SIZE + 16;
	game->player_y = game->player_y * TILE_SIZE + 16;
	init_window(game);

	draw_map(game);
	draw_player(game);

	printf("Player char: %c | Angle: %f\n", game->player_char, game->player_angle);

	// printf("player_char: %c\n", game->player_char);
	// printf("player_x: %f\n", game->player_x);
	// printf("player_y: %f\n", game->player_y);
	// printf("dir_x: %f\n", game->dir_x);
	// printf("dir_y: %f\n", game->dir_y);
	// printf("plane_x: %f\n", game->plane_x);
	// printf("plane_y: %f\n", game->plane_y);

	game->fov = M_PI / 3;
	game->player_angle = normalize_angle(game->player_angle);
	game->pdx = cos(game->player_angle); // Player delta x
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
	mlx_hook(game->win, 17, 0, mlx_loop_end, game->mlx);
	mlx_loop(game->mlx);
}
