/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbakour <zbakour@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 16:48:35 by sodahani          #+#    #+#             */
/*   Updated: 2025/06/12 14:31:36 by zbakour          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <math.h>
# include "get_next_line.h"
# include "mlx.h"
# include <fcntl.h>
# include <stddef.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

#ifndef M_PI
# define M_PI 3.14159265358979323846
#endif
# define FT_ALLOC 1
# define FT_CLEAR 0
# define MAX_LINES 100
# define TILE 64
# define MAP_WIDTH 800
# define MAP_HEIGHT 600
# define FOV (M_PI / 3)

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}					t_list;

typedef struct s_texture {
	void	*img;        // Pointer to the image (from mlx_xpm_file_to_image)
	char	*addr;       // Pointer to the pixel data
	int		width;       // Width of the image in pixels
	int		height;      // Height of the image in pixels
	int		bpp;         // Bits per pixel
	int		line_len;    // Number of bytes in one row
	int		endian;      // Byte order
}	t_texture;

typedef struct s_game
{
	// MiniLibX
	void			*mlx;
	void			*win;

	// Map and file
	char			**map;
	char			**map_section;
	char			**map_copy;
	int				fd;
	int				map_start_index;
	int				max_len;

	// Colors
	int				floor_color[3];
	int				ceiling_color[3];

	// Filepaths for XPMs (optional if loading from string earlier)
	char			*north_texture;
	char			*south_texture;
	char			*west_texture;
	char			*east_texture;
	char			*door_closed;
	char			*door_open;
	char			*key;
	char			*anim_0;
	char			*anim_1;

	// Rendering and raycasting
	double			distances_x;
	double			distances_y;
	double			ray_angle;
	double			angle;

	// Config
	// t_texture	*no_texture;
	// t_texture	*so_texture;
	// t_texture	*we_texture;
	// t_texture	*ea_texture;
	// t_texture	*closed_door;
	// t_texture	*open_door;
	// t_texture	*key;
	// t_texture	*anim_0;
	// t_texture	*anim_1;

	// Player info
	float			player_x;
	float			player_y;
	char			player_char;
	float			dir_x;
	float			dir_y;
	float			plane_x;
	float			plane_y;
}	t_game;

void				ft_lstadd_back(t_list **lst, t_list *new);
void				ft_lstclear(t_list **lst, void (*del)(void *));
t_list				*ft_lstnew(void *content);
char				**ft_split2(char *str, char *charset);
char				*ft_strcpy(char *dest, char const *src);
char				*ft_strcat(char *dest, char const *src);
char				*ft_strjoin(char const *s1, char const *s2);
char				*ft_strdup(const char *src);
size_t				ft_strlen(const char *c);
void				*ft_memset(void *s, int c, size_t n);
int					ft_strncmp(const char *s1, const char *s2, size_t n);
char				*ft_strndup(const char *s, size_t n);
t_list				*mem_alloc(size_t size);
void				*ft_malloc(size_t size, short option);
int					parse_map(const char *file_path, t_game *game);
void				handle_init_errors(int error_type);
void				ft_putstr_fd(char *str, int fd);
void				read_map_lines(t_game *game);
char				*extract_path(char *str);
void				validate_configuration_lines(t_game *game);
int					is_empty_line(char *str);
int					ft_isdigit(int c);
int					ft_atoi(const char *str);
int					is_all_digits(const char *str);
size_t				ft_strlcpy(char *dest, const char *src, size_t size);
char				*ft_strtrim(char const *s1, char const *set);
void				extract_number(char *str, t_game *game, int number);
void				check_xpm(t_game *game);
void				map_section(t_game *game);
int					ft_strcmp(const char *s1, const char *s2);
int					is_config_identifier(char *line);
void				handle_texture_line(char *line, char **texture, int *count);
void				handle_color_line(char *line, t_game *game, int type,
						int *count);
void				process_no_so(t_game *game, int *config_count, char *line,
						int *flags);
int					process_config_lines(t_game *game, int *config_flags);
void				validate_configuration_lines(t_game *game);
void				set_up_map(t_game *game);
void				flood_fill(char **map, int y, int x);
void				set_player_direction(t_game *game);
void				process_door(t_game *game, int *config_count, char *line,
						int *flags);
void				process_anim(t_game *game, int *config_count, char *line,
						int *flags);
void				process_key(t_game *game, int *config_count, char *line,
						int *flags);
void				raycasting(t_game *game);

#endif
