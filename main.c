/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sodahani <sodahani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 13:42:18 by zbakour           #+#    #+#             */
/*   Updated: 2025/08/17 10:42:31 by sodahani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void handle_init_errors(int error_type)
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

int main(int ac, char **av)
{
	t_game *game;

	game = ft_malloc(sizeof(t_game), FT_ALLOC);
	if (ac != 2)
		handle_init_errors(1);
	else if (parse_map(av[1], game) == -1)
		handle_init_errors(2);
	change_to_hex(game);
	raycasting(game);
	ft_malloc(0, FT_CLEAR);
	return (0);
}
