/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sodahani <sodahani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 13:42:18 by zbakour           #+#    #+#             */
/*   Updated: 2025/08/20 09:01:07 by sodahani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/cub3d.h"

void	handle_init_errors(int error_type)
{
	ft_malloc(0, FT_CLEAR);
	if (error_type == 1)
		ft_putstr_fd("Error: \nInvalid arguments\n", 2);
	else if (error_type == 2)
		ft_putstr_fd("Error: \nFailed to parse map\n", 2);
	else if (error_type == 3)
		ft_putstr_fd("Error: \nDuplicate configuration element\n", 2);
	else if (error_type == 4)
		ft_putstr_fd("Error: \nUndefined char\n", 2);
	else if (error_type == 5)
		ft_putstr_fd("Error: \nNo player found or map is big\n", 2);
	else if (error_type == 6)
		ft_putstr_fd("Error: \nMap not closed\n", 2);
	else if (error_type == 7)
		ft_putstr_fd("Error: \ntoo manny doors\n", 2);
	exit(1);
}

static int	reset_mouse_position(t_game *game, int *last_x)
{
	mlx_mouse_move(game->mlx, game->win, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
	*last_x = SCREEN_WIDTH / 2;
	return (0);
}

static void	update_player_angle(t_game *game, int delta_x)
{
	game->player_angle += delta_x * MOUSE_SENSITIVITY;
	game->player_angle = normalize_angle(game->player_angle);
	game->pdx = cos(game->player_angle);
	game->pdy = sin(game->player_angle);
	cast_rays(game);
}

int	mouse_hook(int x, int y, void *param)
{
	t_game		*game;
	static int	last_x = SCREEN_WIDTH / 2;
	long		now;
	static long	last_update = 0;
	int			delta_x;

	game = (t_game *)param;
	now = current_millis();
	if (now - last_update < 65)
		return (1);
	if (x < 0 || x >= SCREEN_WIDTH || y < 0 || y >= SCREEN_HEIGHT)
		return (reset_mouse_position(game, &last_x));
	delta_x = x - last_x;
	if (delta_x != 0)
	{
		last_update = now;
		update_player_angle(game, delta_x);
	}
	last_x = x;
	return (0);
}

int	main(int ac, char **av)
{
	t_game	*game;

	game = ft_malloc(sizeof(t_game), FT_ALLOC);
	if (!game)
		return (0);
	ft_memset(game, 0, sizeof(t_game));
	if (ac != 2)
		handle_init_errors(1);
	else if (parse_map(av[1], game) == -1)
		handle_init_errors(2);
	init_window(game);
	change_to_hex(game);
	init_doors(game);
	raycasting(game);
	close_window(game);
	return (0);
}
