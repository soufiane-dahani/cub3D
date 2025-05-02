/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_configuration_lines.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sodahani <sodahani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 16:48:35 by sodahani          #+#    #+#             */
/*   Updated: 2025/05/02 23:17:15 by sodahani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static void	handle_texture_line(char *line, char **texture, int *count)
{
	*texture = extract_path(line);
	(*count)++;
}

static void	handle_color_line(char *line, t_game *game, int type, int *count)
{
	extract_number(line, game, type);
	(*count)++;
}

static void process_config_line(t_game *game, int *config_count, char *line, int *flags)
{
    while (*line == ' ' || *line == '\t' || *line == '\r')
        line++;
    if (!ft_strncmp(line, "NO ", 3))
    {
        if (flags[0])
            handle_init_errors(3);
        flags[0] = 1;
        handle_texture_line(line, &game->north_texture, config_count);
    }
    else if (!ft_strncmp(line, "SO ", 3))
    {
        if (flags[1])
            handle_init_errors(3);
        flags[1] = 1;
        handle_texture_line(line, &game->south_texture, config_count);
    }
    else if (!ft_strncmp(line, "WE ", 3))
    {
        if (flags[2])
            handle_init_errors(3);
        flags[2] = 1;
        handle_texture_line(line, &game->west_texture, config_count);
    }
    else if (!ft_strncmp(line, "EA ", 3))
    {
        if (flags[3])
            handle_init_errors(3);
        flags[3] = 1;
        handle_texture_line(line, &game->east_texture, config_count);
    }
    else if (!ft_strncmp(line, "F ", 2))
    {
        if (flags[4])
            handle_init_errors(3);
        flags[4] = 1;
        handle_color_line(line, game, 1, config_count);
    }
    else if (!ft_strncmp(line, "C ", 2))
    {
        if (flags[5])
            handle_init_errors(3);
        flags[5] = 1;
        handle_color_line(line, game, 2, config_count);
    }
    else
    {
        ft_putstr_fd("Error: \nInvalid config line\n", 2);
        ft_malloc(0, FT_CLEAR);
        exit(1);
    }
}

void check_duplicate_textures(t_game *game)
{
    if (ft_strcmp(game->north_texture, game->south_texture) == 0 ||
        ft_strcmp(game->north_texture, game->west_texture) == 0 ||
        ft_strcmp(game->north_texture, game->east_texture) == 0 ||
        ft_strcmp(game->south_texture, game->west_texture) == 0 ||
        ft_strcmp(game->south_texture, game->east_texture) == 0 ||
        ft_strcmp(game->west_texture, game->east_texture) == 0)
    {
        ft_putstr_fd("Error: \nDuplicate texture files are not allowed\n", 2);
        ft_malloc(0, FT_CLEAR);
        exit(1);
    }
}

void validate_configuration_lines(t_game *game)
{
    int config_count;
    int i;
    int config_flags[6] = {0};

    config_count = 0;
    i = 0;
    while (config_count < 6 && game->map[i])
    {
        if (is_empty_line(game->map[i]))
        {
            i++;
            continue;
        }
        process_config_line(game, &config_count, game->map[i], config_flags);
        i++;
    }
    if (config_count != 6)
        handle_init_errors(2);
    check_duplicate_textures(game);
    
    check_xpm(game);
}


