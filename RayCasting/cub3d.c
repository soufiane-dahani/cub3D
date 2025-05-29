/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obarais <obarais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 16:48:35 by sodahani          #+#    #+#             */
/*   Updated: 2025/05/29 20:37:32 by obarais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int is_wall(double x, double y, t_game **game)
{
    int map_x = (int)(x);
    int map_y = (int)(y);

    if (map_x < 0 || map_y < 0 || map_x >= MAP_WIDTH || map_y >= MAP_HEIGHT)
        return 1;
    return (*game)->map_section[map_y / TILE][map_x / TILE];
}

int key_hook(int keycode, t_game **game)
{
    if (keycode == 65307)
        exit(0);
    if (keycode == 100)
		(*game)->angle += 0.1; // Left
    if (keycode == 97)
		(*game)->angle -= 0.1; // Right
    if (keycode == 119)
	{ // Up
        double nx = (*game)->player_x - cos((*game)->angle) * 4;
        double ny = (*game)->player_y - sin((*game)->angle) * 4;
        if (is_wall(nx, ny, game) != 1)
		{
			(*game)->player_x = nx;
			(*game)->player_y = ny;
		}
    }
    if (keycode == 115)
	{ // Down
        double nx = (*game)->player_x + cos((*game)->angle) * 5;
        double ny = (*game)->player_y + sin((*game)->angle) * 5;
        if (is_wall(nx, ny, game) != 1)
		{
			(*game)->player_x = nx;
			(*game)->player_y = ny;
		}
    }
    return 0;
}

void	chose_the_angle_p(t_game **game)
{
	if (*game)
	{
		if ((*game)->player_char == 'N')
			(*game)->angle = M_PI / 2;
		else if ((*game)->player_char == 'S')
			(*game)->angle = 3 * M_PI / 2;
		else if ((*game)->player_char == 'E')
			(*game)->angle = 0;
		else if ((*game)->player_char == 'W')
			(*game)->angle = M_PI;
	}
}

void	the_distance_with_x(t_game **game)
{
	int a_x, a_y;
	double dt = 0;
	double distance_to_a = 0;

	a_x = (*game)->player_x / TILE ;
	a_x = a_x * TILE;
	if ((*game)->ray_angle < M_PI / 2 || (*game)->ray_angle > (3 * M_PI) / 2)
		a_x += TILE;
	a_y = (*game)->player_y + ((a_x - (*game)->player_x) * tan((*game)->ray_angle));
	distance_to_a = sqrt(pow(fabs((*game)->player_x - a_x), 2) + pow(fabs((*game)->player_y - a_y), 2));
	dt = sqrt(pow(TILE, 2) + pow(TILE * tan((*game)->ray_angle), 2));
	while (1)
	{
		if (a_x < 0 || a_y < 0 || a_x > MAP_WIDTH || a_y > MAP_HEIGHT)
		{
			(*game)->distances_x = distance_to_a;
			return ;
		}
		if ((*game)->map_section[a_y / TILE][a_x / TILE] == '1')
		{
			(*game)->distances_x = distance_to_a;
			return ;
		}
		distance_to_a += dt;
		a_x += TILE * tan((*game)->ray_angle);
		a_y += TILE / tan((*game)->ray_angle);
	}
}

void	the_distance_with_y(t_game **game)
{
	int a_x, a_y;
	double dt = 0;
	double distance_to_a = 0;

	a_y = (*game)->player_y / TILE ;
	a_y = a_y * TILE;
	if ((*game)->ray_angle > M_PI)
		a_y += TILE;
	a_x = (*game)->player_x + (((*game)->player_y - a_y) / tan((*game)->ray_angle));
	distance_to_a = sqrt(pow(fabs((*game)->player_x - a_x), 2) + pow(fabs((*game)->player_y - a_y), 2));
	dt = sqrt(pow(TILE, 2) + pow(TILE / tan((*game)->ray_angle), 2));
	while (1)
	{
		if (a_x < 0 || a_y < 0 || a_x > MAP_WIDTH || a_y > MAP_HEIGHT)
		{
			(*game)->distances_x = distance_to_a;
			return ;
		}
		if ((*game)->map_section[a_y / TILE][a_x / TILE] == '1')
		{
			(*game)->distances_y = distance_to_a;
			return ;
		}
		distance_to_a += dt;
		a_x += TILE / tan((*game)->ray_angle);
		a_y += TILE * tan((*game)->ray_angle);
	}
}

void	get_the_distance(t_game **game, int i)
{
	double step_angle = FOV / MAP_WIDTH;

	(*game)->ray_angle = (*game)->ray_angle + (i * step_angle);
	if ((*game)->ray_angle >= 2 * M_PI)
		(*game)->ray_angle -= 2 * M_PI;
	else if ((*game)->ray_angle < 0)
		(*game)->ray_angle += 2 * M_PI;

	if ((*game)->ray_angle != 0 || (*game)->ray_angle != M_PI)
		the_distance_with_y(game);
	if ((*game)->ray_angle != M_PI / 2 || (*game)->ray_angle != (3 * M_PI) / 2)
		the_distance_with_x(game);
}

void	drow_roof(t_game **game, int start, int x)
{
	int y;

	y = 0;
	while (y < (MAP_HEIGHT / 2 - start))
	{
		mlx_pixel_put((*game)->mlx, (*game)->win, x, y, 0Xeb9234);
		y++;
	}
}

int	loop_hook(t_game **game)
{
	mlx_pixel_put((*game)->mlx, (*game)->win, (*game)->player_x, (*game)->player_y, 0xfffff);
	mlx_pixel_put((*game)->mlx, (*game)->win, (*game)->player_x, (*game)->player_y + 1, 0xfffff);
	mlx_pixel_put((*game)->mlx, (*game)->win, (*game)->player_x, (*game)->player_y + 2, 0xfffff);
	mlx_pixel_put((*game)->mlx, (*game)->win, (*game)->player_x, (*game)->player_y + 3, 0xfffff);
	mlx_pixel_put((*game)->mlx, (*game)->win, (*game)->player_x, (*game)->player_y + 4, 0xfffff);
	mlx_pixel_put((*game)->mlx, (*game)->win, (*game)->player_x, (*game)->player_y + 5, 0xfffff);
	int i;
	int j = 8;
	double	dis_ray;

	i = 0;
	(*game)->distances_x = 0;
	(*game)->distances_y = 0;
	(*game)->ray_angle = (*game)->angle - (FOV / 2);
	while (i < MAP_WIDTH)
	{
		get_the_distance(game, i);
		if ((*game)->distances_x && (*game)->distances_y)
		{
			if ((*game)->distances_x > (*game)->distances_y)
				dis_ray = (*game)->distances_y;
			else
				dis_ray = (*game)->distances_x;
		}
		else
		{
			if ((*game)->distances_x == 0)
				dis_ray = (*game)->distances_y;
			else if ((*game)->distances_y == 0)
				dis_ray = (*game)->distances_x;
		}
		dis_ray = 20;
		// j += 1;
		drow_roof(game, j, i);
		// drow_wall(game, dis_ray, i);
		// drow_floor(game, dis_ray, i);
		i++;
	}
	return (0);
}

void	raycaster(t_game **game)
{
	(*game)->mlx = mlx_init();
	if (!(*game)->mlx)
	{
		ft_malloc(0, FT_CLEAR);
		ft_putstr_fd("Error: \nFailed to initialize mlx\n", 2);
		exit(1);
	}
	(*game)->win = mlx_new_window((*game)->mlx, MAP_WIDTH, MAP_HEIGHT, "Cub3D");
	if (!(*game)->win)
	{
		ft_malloc(0, FT_CLEAR);
		ft_putstr_fd("Error: \nFailed to create window\n", 2);
		exit(1);
	}
	chose_the_angle_p(game);
	(*game)->player_x *= TILE;
	(*game)->player_y *= TILE;
	mlx_hook((*game)->win, 2, 1L, key_hook, game);
	mlx_loop_hook((*game)->mlx, loop_hook, game);
	mlx_hook((*game)->win, 17, 0, mlx_loop_end, (*game)->mlx);
	mlx_loop((*game)->mlx);
}
