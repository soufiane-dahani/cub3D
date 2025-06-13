/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbakour <zbakour@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 22:48:03 by obarais           #+#    #+#             */
/*   Updated: 2025/06/13 04:12:06 by zbakour          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void cast_ray(t_game *game)
{
	
}

void put_pixels(t_game *game, int x, int y, int color)
{
    int bpp, line_length, endian;
    char *data = mlx_get_data_addr(game->img, &bpp, &line_length, &endian);
    if (x >= 0 && x < SCREEN_WIDTH && y >= 0 && y < MAP_HEIGHT)
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

void cast_rays(t_game *game)
{
    double angle_step = game->fov / game->num_rays;
    int bpp, line_length, endian;
    char *data = mlx_get_data_addr(game->img, &bpp, &line_length, &endian);

    for (int i = 0; i < game->num_rays; i++)
    {
        double ray_angle = game->start_angle + i * angle_step;
        ray_angle = normalize_angle(ray_angle);

        // Ray starting position (player center in pixels)
        double ray_x = game->player_x + (TILE_SIZE / 4) / 2;
        double ray_y = game->player_y + (TILE_SIZE / 4) / 2;

        // Ray direction
        double ray_dx = cos(ray_angle);
        double ray_dy = sin(ray_angle);

        // Step until wall or out of bounds (simple DDA)
        int dof = 0;
        while (dof < 30)
        {
            int map_x = (int)(ray_x / TILE_SIZE);
            int map_y = (int)(ray_y / TILE_SIZE);
            if (map_x < 0 || map_x >= 16 || map_y < 0 || map_y >= 8)
                break;
            ray_x += ray_dx * 0.5; // step size (2 pixels per step)
            ray_y += ray_dy * 0.5;
			// Check for wall hit

			if (game->map_section[map_y][map_x] == '1')
			{
				// Wall hit
				printf("Ray {%d} hit wall at (%d, %d)\n", i, map_x, map_y);
				break;
			}
			ray_x += ray_dx * 2;
			ray_y += ray_dy * 2;
			
			if (game->map_section[map_y][map_x] == '0')
			{
				// Empty space, continue stepping
				// printf("Ray in empty space at (%d, %d)\n", map_x, map_y);
				// ray_x += ray_dx * 5; // step size (2 pixels per step)
				// ray_y += ray_dy * 5;
			
				continue;
			}
			dof++;
				
        }
		
        // Draw the ray using your draw_line function
		int color = 0x7FFFD4;
		draw_line(game, (int)game->player_x + (TILE_SIZE / 4) / 2, (int)game->player_y + (TILE_SIZE / 4) / 2, (int)ray_x , (int)ray_y, color);
    }
    mlx_put_image_to_window(game->mlx, game->win, game->img, 0, 0);
}


void raycasting(t_game *game)
{
	game->player_x = game->player_x * TILE_SIZE;
	game->player_y = game->player_y * TILE_SIZE;
	init_window(game);
	
	draw_map(game);
	draw_player(game);


	printf("player_char: %c\n", game->player_char);
	printf("player_x: %f\n", game->player_x);
	printf("player_y: %f\n", game->player_y);
	printf("dir_x: %f\n", game->dir_x);
	printf("dir_y: %f\n", game->dir_y);
	printf("plane_x: %f\n", game->plane_x);
	printf("plane_y: %f\n", game->plane_y);
	
	define_player_angle(game);
	game->pdx = cos(game->player_angle) * 5; // Player delta x
	game->pdy = sin(game->player_angle) * 5; // Player delta y
	game->fov = M_PI / 3;
	game->start_angle = game->player_angle - (game->fov / 2);
	game->end_angle = game->player_angle + (game->fov / 2);
	game->num_rays = SCREEN_WIDTH / TILE_SIZE;
	// game->player_x *= TILE_SIZE;
	// game->player_y *= TILE_SIZE;
	printf("Player FOV Range: (%.6f, %.6f)\n", game->end_angle, game->start_angle);
	printf("Player FOV: (%f, %f)\n", game->start_angle, game->end_angle);
	printf("Player angle: %f\n", game->player_angle);
	printf("Number of rays: %d\n", game->num_rays);

	

	
	cast_rays(game);
	mlx_hook(game->win, 2, 1L << 0, key_hook, game);
	// mlx_loop_hook(game->mlx, loop_hook, game);
	mlx_hook(game->win, 17, 0, mlx_loop_end, game->mlx);
	mlx_loop(game->mlx);

}
