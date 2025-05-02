/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sodahani <sodahani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 16:48:35 by sodahani          #+#    #+#             */
/*   Updated: 2025/05/02 17:30:09 by sodahani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "get_next_line.h"
# include <fcntl.h>
# include <stddef.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

# define FT_ALLOC 1
# define FT_CLEAR 0
# define MAX_LINES 100

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}					t_list;

typedef struct s_game
{
	void			*mlx;
	void			*win;
	int				win_width;
	int				win_height;
	char			**map;
	int				rows;
	int				cols;
	int				fd;
	char			*north_texture;
	char			*south_texture;
	char			*west_texture;
	char			*east_texture;
	int				floor_color[3];
	int				ceiling_color[3];

}					t_game;

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

#endif