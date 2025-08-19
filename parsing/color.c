/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbakour <zbakour@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 16:48:35 by sodahani          #+#    #+#             */
/*   Updated: 2025/08/19 18:44:18 by zbakour          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	get_color(int rgb[3])
{
	int	red;
	int	green;
	int	blue;

	red = rgb[0];
	green = rgb[1];
	blue = rgb[2];
	return (red << 16 | green << 8 | blue);
}

void	change_to_hex(t_game *game)
{
	game->floor = mlx_get_color_value(game->mlx, get_color(game->floor_color));
	game->ceiling = mlx_get_color_value(game->mlx,
			get_color(game->ceiling_color));
}

void	render_animation(t_game *game)
{
	t_texture	*frame;
	int			start_x;
	int			start_y;
	int			x;
	int			y;

	frame = &game->anim_textures[game->anim.current_frame];
	start_x = (SCREEN_WIDTH - frame->width) / 2;
	start_y = SCREEN_HEIGHT - frame->height;
	y = 0;
	while (y < frame->height)
	{
		x = 0;
		while (x < frame->width)
		{
			if ((get_texture_color(frame, x, y) & 0x00FFFFFF) != 0)
				put_pixels(game, start_x + x, start_y + y,
					get_texture_color(frame, x, y));
			x++;
		}
		y++;
	}
}

void	update_animation(t_game *game)
{
	if (!game->anim.playing)
		return ;
	game->anim.frame_counter++;
	if (game->anim.frame_counter >= game->anim.frame_delay)
	{
		game->anim.frame_counter = 0;
		game->anim.current_frame++;
		if (game->anim.current_frame > 3)
		{
			game->anim.current_frame = 0;
			game->anim.playing = 0;
		}
	}
}
