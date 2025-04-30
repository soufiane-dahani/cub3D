/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sodahani <sodahani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 16:48:35 by sodahani          #+#    #+#             */
/*   Updated: 2025/04/30 15:08:24 by sodahani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	search_cub(const char *file_path)
{
	size_t	len;

	if (!file_path)
		return (0);
	len = ft_strlen(file_path);
	if (len < 4)
		return (0);
	return (file_path[len - 4] == '.' && file_path[len - 3] == 'c'
		&& file_path[len - 2] == 'u' && file_path[len - 1] == 'b');
}

int parse_map(const char *file_path, t_game *game)
{
    if (!search_cub(file_path))
    {
        if (file_path)
			write(STDERR_FILENO, "Error: \nFile should be .cub\n", 28);
		return (-1);
    }
    game->fd = open(file_path, O_RDONLY);
    printf("%d\n" ,game->fd);
    return 0;
}
