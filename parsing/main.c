/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sodahani <sodahani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 16:48:35 by sodahani          #+#    #+#             */
/*   Updated: 2025/05/01 22:48:42 by sodahani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	handle_init_errors(int error_type)
{
	ft_malloc(0, FT_CLEAR);
	if (error_type == 1)
		write(STDERR_FILENO, "Error: \nInvalid arguments\n", 24);
	else if (error_type == 2)
		write(STDERR_FILENO, "Error: \nFailed to parse map\n", 28);
	else if (error_type == 3)
	{
		//cleanup_game(game);
		write(STDERR_FILENO, "Error: \nInvalid map\n", 20);
	}
	else if (error_type == 4)
	{
		//cleanup_game(game);
		write(STDERR_FILENO, "Error: \nMLX initialization failed\n", 31);
	}
	exit(1);
}

int	main(int ac, char **av)
{
	t_game	*game;

	game = ft_malloc(sizeof(t_game), FT_ALLOC);
	if (ac != 2)
		handle_init_errors(1);
	else if (parse_map(av[1], game) == -1)
		handle_init_errors(2);
	ft_malloc(0, FT_CLEAR);
	return (0);
}
