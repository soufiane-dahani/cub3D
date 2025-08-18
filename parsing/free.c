/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sodahani <sodahani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 16:48:35 by sodahani          #+#    #+#             */
/*   Updated: 2025/08/18 20:14:54 by sodahani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	free_textures(t_game *game)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		if (game->anim_textures[i].img)
			mlx_destroy_image(game->mlx, game->anim_textures[i].img);
		i++;
	}
}

static void	cleanup_textures(t_game *game)
{
	t_texture	*textures[9];
	int			i;

	textures[0] = &game->no_texture;
	textures[1] = &game->so_texture;
	textures[2] = &game->we_texture;
	textures[3] = &game->ea_texture;
	textures[4] = &game->door_closed_texture;
	textures[5] = &game->anim_0_texture;
	textures[6] = &game->anim_1_texture;
	textures[7] = &game->anim_2_texture;
	textures[8] = &game->anim_3_texture;
	i = 0;
	while (i < 9)
	{
		if (textures[i]->img)
			mlx_destroy_image(game->mlx, textures[i]->img);
		i++;
	}
}

void	cleanup_game(t_game *game)
{
	if (!game)
		return ;
	if (game->img)
		mlx_destroy_image(game->mlx, game->img);
	cleanup_textures(game);
	free_textures(game);
	if (game->win)
		mlx_destroy_window(game->mlx, game->win);
	if (game->mlx)
	{
		mlx_destroy_display(game->mlx);
		free(game->mlx);
	}
	ft_malloc(0, FT_CLEAR);
}

int	close_window(t_game *game)
{
	cleanup_game(game);
	exit(0);
	return (0);
}
