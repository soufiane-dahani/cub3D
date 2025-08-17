/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_textures.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sodahani <sodahani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 10:46:47 by sodahani          #+#    #+#             */
/*   Updated: 2025/08/17 10:58:19 by sodahani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void load_single_texture(void *mlx, t_texture *tex, char *path, char *error_msg)
{
	int width;
	int height;

	tex->img = mlx_xpm_file_to_image(mlx, path, &width, &height);
	if (!tex->img)
	{
		ft_putstr_fd(error_msg, 2);
		ft_putstr_fd("\n", 2);
		ft_malloc(0, FT_CLEAR);
		exit(1);
	}
	if (!path)
	{
		ft_putstr_fd("Texture path is NULL\n", 2);
		ft_malloc(0, FT_CLEAR);
		exit(1);
	}
	tex->addr = mlx_get_data_addr(tex->img, &tex->bpp, &tex->line_len, &tex->endian);
	tex->width = width;
	tex->height = height;
}


void load_textures(t_game *game)
{
	load_single_texture(game->mlx, &game->no_texture, game->north_texture, "Failed to load north texture\n");
	load_single_texture(game->mlx, &game->so_texture, game->south_texture, "Failed to load south texture\n");
	load_single_texture(game->mlx, &game->we_texture, game->west_texture, "Failed to load west texture\n");
	load_single_texture(game->mlx, &game->ea_texture, game->east_texture, "Failed to load east texture\n");
	load_single_texture(game->mlx, &game->anim_0_texture, game->anim_0, "Failed to load anim_0 texture\n");
	load_single_texture(game->mlx, &game->anim_1_texture, game->anim_1, "Failed to load anim_1 texture\n");
	load_single_texture(game->mlx, &game->door_closed_texture, game->door_closed, "Failed to load door_closed texture\n");
	load_single_texture(game->mlx, &game->anim_3_texture, game->anim_3, "Failed to load anim_3 texture\n");
	load_single_texture(game->mlx, &game->anim_2_texture, game->anim_2, "Failed to load anim_2 texture\n");
}

