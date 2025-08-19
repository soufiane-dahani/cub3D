/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbakour <zbakour@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 16:50:00 by zbakour           #+#    #+#             */
/*   Updated: 2025/08/19 16:50:43 by zbakour          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

// Get color from texture at specific coordinates
int	get_texture_color(t_texture *texture, int x, int y)
{
	char	*pixel;
	int		color;

	if (x < 0 || x >= texture->width || y < 0 || y >= texture->height)
		return (0x000000); // Return black if out of bounds
	pixel = texture->addr + (y * texture->line_len + x * (texture->bpp / 8));
	color = *(int *)pixel;
	return (color);
}

// Determine which texture to use based on wall direction
t_texture	*get_wall_texture(t_game *game, int side, int step_x, int step_y)
{
	if (side == 0) // Vertical wall (hit on x-side)
	{
		if (step_x > 0)
			return (&game->ea_texture); // East wall
		else
			return (&game->we_texture); // West wall
	}
	else if (side == -99)
	{	
		return (&game->door_closed_texture); // South wall
	}
	else // Horizontal wall (hit on y-side)
	{
		if (step_y > 0)
			return (&game->so_texture); // South wall
		else
			return (&game->no_texture); // North wall
	}
}

// Calculate texture coordinate x based on wall hit position
double	get_wall_x(t_game *game, double ray_x, double ray_y, int side)
{
	double	wall_x;
	(void )game;

	if (side == 0) // Vertical wall (hit on x-side)
		wall_x = (ray_y / TILE_SIZE) - floor(ray_y / TILE_SIZE);
	else // Horizontal wall (hit on y-side)
		wall_x = (ray_x / TILE_SIZE) - floor(ray_x / TILE_SIZE);
	return (wall_x);
}
