/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_textures.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sodahani <sodahani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 10:46:47 by sodahani          #+#    #+#             */
/*   Updated: 2025/08/22 19:04:38 by sodahani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	load_single_texture(void *mlx, t_texture *tex, char *path,
		char *error_msg)
{
	int	width;
	int	height;

	if (!path)
	{
		ft_putstr_fd("Texture path is NULL\n", 2);
		return (0);
	}
	tex->img = mlx_xpm_file_to_image(mlx, path, &width, &height);
	if (!tex->img)
	{
		ft_putstr_fd(error_msg, 2);
		ft_putstr_fd("\n", 2);
		return (0);
	}
	tex->addr = mlx_get_data_addr(tex->img, &tex->bpp, &tex->line_len,
			&tex->endian);
	tex->width = width;
	tex->height = height;
	return (1);
}

static void	load_basic_textures(t_game *game)
{
	if (!load_single_texture(game->mlx, &game->no_texture,
			game->north_texture, "Failed to load north texture"))
		close_window(game);
	if (!load_single_texture(game->mlx, &game->so_texture,
			game->south_texture, "Failed to load south texture"))
		close_window(game);
	if (!load_single_texture(game->mlx, &game->we_texture,
			game->west_texture, "Failed to load west texture"))
		close_window(game);
	if (!load_single_texture(game->mlx, &game->ea_texture,
			game->east_texture, "Failed to load east texture"))
		close_window(game);
	if (!load_single_texture(game->mlx, &game->door_closed_texture,
			game->door_closed, "Failed to load door_closed texture"))
		close_window(game);
}

static void	load_animation_textures(t_game *game)
{
	if (!load_single_texture(game->mlx, &game->anim_textures[0],
			game->anim_0, "Failed to load anim_0 texture"))
		close_window(game);
	if (!load_single_texture(game->mlx, &game->anim_textures[1],
			game->anim_1, "Failed to load anim_1 texture"))
		close_window(game);
	if (!load_single_texture(game->mlx, &game->anim_textures[2],
			game->anim_2, "Failed to load anim_2 texture"))
		close_window(game);
	if (!load_single_texture(game->mlx, &game->anim_textures[3],
			game->anim_3, "Failed to load anim_3 texture"))
		close_window(game);
}

void	load_textures(t_game *game)
{
	load_basic_textures(game);
	load_animation_textures(game);
	game->anim.current_frame = 0;
	game->anim.playing = 0;
	game->anim.frame_delay = 0.9;
	game->anim.frame_counter = 0;
}
