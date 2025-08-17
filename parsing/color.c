/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sodahani <sodahani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 16:48:35 by sodahani          #+#    #+#             */
/*   Updated: 2025/08/17 09:56:12 by sodahani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static char to_hex_digit(int value)
{
    if (value < 10)
        return '0' + value;
    else
        return 'A' + (value - 10);
}

static void rgb_to_hex(int rgb[3], char hex[8])
{

    hex[0] = '#';
    hex[1] = to_hex_digit(rgb[0] / 16);
    hex[2] = to_hex_digit(rgb[0] % 16);
    hex[3] = to_hex_digit(rgb[1] / 16);
    hex[4] = to_hex_digit(rgb[1] % 16);
    hex[5] = to_hex_digit(rgb[2] / 16);
    hex[6] = to_hex_digit(rgb[2] % 16);
    hex[7] = '\0';
}
void change_to_hex(t_game *game)
{
    rgb_to_hex(game->floor_color, game->hex_floor);
    rgb_to_hex(game->ceiling_color, game->hex_ceiling);
}
