/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.bak.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbakour <zbakour@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 22:48:03 by obarais           #+#    #+#             */
/*   Updated: 2025/06/12 14:10:43 by zbakour          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	is_wall(double x, double y, t_game **game)
{
	int map_x = (int)(x / TILE);
	int map_y = (int)(y / TILE);

	if (map_x < 0 || map_y < 0 || map_x >= MAP_WIDTH / TILE || map_y >= MAP_HEIGHT / TILE)
		return (1);
	return ((*game)->map_section[map_y][map_x] == '1');
}

void	normalize_angle(double *angle)
{
	while (*angle < 0)
		*angle += 2 * M_PI;
	while (*angle >= 2 * M_PI)
		*angle -= 2 * M_PI;
}

void	the_distance_with_x(t_game **game)
{
	double	x, y;
	double	step_x, step_y;
	double	distance;

	x = floor((*game)->player_x / TILE) * TILE;

	y = (*game)->player_y + (x - (*game)->player_x) * tan((*game)->ray_angle);

	step_x = TILE;

	step_y = TILE * tan((*game)->ray_angle);

	while (x >= 0 && y >= 0 && x < MAP_WIDTH && y < MAP_HEIGHT)
	{
		int map_x = (int)x / TILE;
		int map_y = (int)y / TILE;

		if ((*game)->map_section[map_y][map_x] == '1')
			break;
		x += step_x;
		y += step_y;
	}

	distance = sqrt(pow(x - (*game)->player_x, 2) + pow(y - (*game)->player_y, 2));
	(*game)->distances_x = distance;
}


void	the_distance_with_y(t_game **game)
{
	double	x, y;
	double	step_x, step_y;
	double	distance;

	y = floor((*game)->player_y / TILE) * TILE;

	x = (*game)->player_x + (y - (*game)->player_y) / tan((*game)->ray_angle);

	step_y = TILE;

	step_x = TILE / tan((*game)->ray_angle);

	while (x >= 0 && y >= 0 && x < MAP_WIDTH && y < MAP_HEIGHT)
	{
		int map_x = (int)x / TILE;
		int map_y = (int)y / TILE;
		if ((*game)->map_section[map_y][map_x] == '1')
			break;
		x += step_x;
		y += step_y;
	}

	distance = sqrt(pow(x - (*game)->player_x, 2) + pow(y - (*game)->player_y, 2));
	(*game)->distances_y = distance;
}


double	dda(t_game **game, double ray_angle)
{
	(*game)->ray_angle = ray_angle;

	the_distance_with_y(game);
	the_distance_with_x(game);

	if ((*game)->distances_x && (*game)->distances_y)
		return fmin((*game)->distances_x, (*game)->distances_y);
	else if ((*game)->distances_x)
		return (*game)->distances_x;
	else
		return (*game)->distances_y;
}

int	key_hook(int keycode, t_game **game)
{
	double nx = 0.0;
	double ny = 0.0;

	if (keycode == 65307)
		exit(0);
	else if (keycode == 65363) // D
		(*game)->angle += 0.1;
	else if (keycode == 65361) // A
		(*game)->angle -= 0.1;
	else if (keycode == 100)
	{
		nx = (*game)->player_x - cos((*game)->angle - (M_PI / 2)) * 4;
		ny = (*game)->player_y - sin((*game)->angle - (M_PI / 2)) * 4;
		if (!is_wall(nx, ny, game))
		{
			(*game)->player_x = nx;
			(*game)->player_y = ny;
		}
	}
	else if (keycode == 97)
	{
		nx = (*game)->player_x - cos((*game)->angle + (M_PI / 2)) * 4;
		ny = (*game)->player_y - sin((*game)->angle + (M_PI  / 2)) * 4;
		if (!is_wall(nx, ny, game))
		{
			(*game)->player_x = nx;
			(*game)->player_y = ny;
		}
	}
	else if (keycode == 119) // W
	{
		nx = (*game)->player_x + cos((*game)->angle) * 4;
		ny = (*game)->player_y + sin((*game)->angle) * 4;
		if (!is_wall(nx, ny, game))
		{
			(*game)->player_x = nx;
			(*game)->player_y = ny;
		}
	}
	else if (keycode == 115) // S
	{
		nx = (*game)->player_x - cos((*game)->angle) * 4;
		ny = (*game)->player_y - sin((*game)->angle) * 4;
		if (!is_wall(nx, ny, game))
		{
			(*game)->player_x = nx;
			(*game)->player_y = ny;
		}
	}
	return (0);
}

void	draw_column(t_game **game, int x, double dist)
{
	int	wall_height;
	double dis_projected_plan;
	int	y;
	int	start;

	dis_projected_plan = (MAP_WIDTH / 2) / tan(FOV / 2);

	wall_height = (TILE / dist) * dis_projected_plan;
	if (wall_height > MAP_HEIGHT)
		wall_height = MAP_HEIGHT;
	start = (MAP_HEIGHT / 2) - (wall_height / 2);
	y = 0;

	while (y < start)
		mlx_pixel_put((*game)->mlx, (*game)->win, x, y++, 0x222222);
	while (y < start + wall_height)
		mlx_pixel_put((*game)->mlx, (*game)->win, x, y++, 0xffffff);
	while (y < MAP_HEIGHT)
		mlx_pixel_put((*game)->mlx, (*game)->win, x, y++, 0x444444);
}

int	loop_hook(t_game **game)
{
	int		x = 0;
	double	step = FOV / MAP_WIDTH;
	double	ray_angle;

	ray_angle = (*game)->angle - (FOV / 2);
	while (x < MAP_WIDTH)
	{
		normalize_angle(&ray_angle);
		(*game)->ray_angle = ray_angle;
		double dist = dda(game, ray_angle);
		draw_column(game, x, dist);
		ray_angle += step;
		x++;
	}
	return (0);
}

void	chose_the_angle_p(t_game **game)
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

void	raycaster(t_game **game)
{
	(*game)->mlx = mlx_init();
	if (!(*game)->mlx)
	{
		ft_putstr_fd("Error initializing MLX\n", 2);
		exit(1);
	}
	(*game)->win = mlx_new_window((*game)->mlx, MAP_WIDTH, MAP_HEIGHT, "Cub3D");
	if (!(*game)->win)
	{
		ft_putstr_fd("Error creating window\n", 2);
		exit(1);
	}
	chose_the_angle_p(game);
	(*game)->player_x *= TILE;
	(*game)->player_y *= TILE;
	mlx_hook((*game)->win, 2, 1L << 0, key_hook, game);
	mlx_loop_hook((*game)->mlx, loop_hook, game);
	mlx_hook((*game)->win, 17, 0, mlx_loop_end, (*game)->mlx);
	mlx_loop((*game)->mlx);
}
