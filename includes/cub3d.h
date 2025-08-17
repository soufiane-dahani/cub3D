/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sodahani <sodahani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 16:48:35 by sodahani          #+#    #+#             */
/*   Updated: 2025/08/17 21:04:00 by sodahani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
#define CUB3D_H

#include <math.h>
#include "get_next_line.h"
#include "mlx.h"
#include <fcntl.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <sys/time.h>

#define ESC_KEY 65307
#define SPACE_KEY 32
#define D_KEY 100
#define A_KEY 97
#define W_KEY 119
#define S_KEY 115
#define RIGHT_ARROW 65363
#define LEFT_ARROW 65361
#define MOVE_SPEED 5
#define ROTATION_SPEED 0.05

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

#define FT_ALLOC 1
#define FT_CLEAR 0
#define MAX_LINES 100

#define TILE_SIZE 64
#define SCREEN_WIDTH 1024
#define MAP_HEIGHT 512

#define MAX_KEYS 256

typedef struct s_list
{
	void *content;
	struct s_list *next;
} t_list;

typedef struct s_texture
{
	void *img;
	char *addr;
	int width;
	int height;
	int bpp;
	int line_len;
	int endian;
} t_texture;

typedef struct s_door {
    int x;
    int y;
    int is_open;
} t_door;

typedef struct s_anim {
    int current_frame;
    int playing;
    double frame_delay;
    double frame_counter;
} t_anim;

 


typedef struct s_game
{
	// MiniLibX
	void *mlx;
	void *win;

	// Map and file
	char **map;
	char **map_section;
	char **map_copy;
	int fd;
	int map_start_index;
	int max_len;

	// Colors
	int floor_color[3];
	int ceiling_color[3];
	int floor;
	int ceiling;

	// Filepaths for XPMs (optional if loading from string earlier)
	char *north_texture;
	char *south_texture;
	char *west_texture;
	char *east_texture;
	char *door_closed;
	char *anim_3;
	char *anim_2;
	char *anim_0;
	char *anim_1;

	// Config
	t_texture no_texture;
	t_texture so_texture;
	t_texture we_texture;
	t_texture ea_texture;
	t_texture door_closed_texture;
	t_texture anim_3_texture;
	t_texture anim_2_texture;
	t_texture anim_0_texture;
	t_texture anim_1_texture;
	t_door	doors[4];
	t_anim      anim;
	t_texture anim_textures[4];
	// void *frames[4];
	int		num_doors;
	
	// Player info
	float player_x; // player x pos on arr
	float player_y; // player y pos on arr

	char player_char;
	float dir_x;
	float dir_y;
	float plane_x;
	float plane_y;

	// Rendering and raycasting
	int map_width;
	int map_height;
	double start_angle;
	double end_angle;
	int num_rays;
	double ray_angle;
	double player_angle;
	double fov;
	double pdx;
	double pdy;
	int screen_width;
	int screen_height;
	void *img;

} t_game;

void ft_lstadd_back(t_list **lst, t_list *new);
void ft_lstclear(t_list **lst, void (*del)(void *));
t_list *ft_lstnew(void *content);
char **ft_split2(char *str, char *charset);
char *ft_strcpy(char *dest, char const *src);
char *ft_strcat(char *dest, char const *src);
char *ft_strjoin(char const *s1, char const *s2);
char *ft_strdup(const char *src);
size_t ft_strlen(const char *c);
void *ft_memset(void *s, int c, size_t n);
int ft_strncmp(const char *s1, const char *s2, size_t n);
char *ft_strndup(const char *s, size_t n);
t_list *mem_alloc(size_t size);
void *ft_malloc(size_t size, short option);
int parse_map(const char *file_path, t_game *game);
void handle_init_errors(int error_type);
void ft_putstr_fd(char *str, int fd);
void read_map_lines(t_game *game);
char *extract_path(char *str);
void validate_configuration_lines(t_game *game);
int is_empty_line(char *str);
int ft_isdigit(int c);
int ft_atoi(const char *str);
int is_all_digits(const char *str);
size_t ft_strlcpy(char *dest, const char *src, size_t size);
char *ft_strtrim(char const *s1, char const *set);
void extract_number(char *str, t_game *game, int number);
void check_xpm(t_game *game);
void map_section(t_game *game);
int ft_strcmp(const char *s1, const char *s2);
int is_config_identifier(char *line);
void handle_texture_line(char *line, char **texture, int *count);
void handle_color_line(char *line, t_game *game, int type,
					   int *count);
void process_no_so(t_game *game, int *config_count, char *line,
				   int *flags);
int process_config_lines(t_game *game, int *config_flags);
void validate_configuration_lines(t_game *game);
void set_up_map(t_game *game);
void flood_fill(char **map, int y, int x);
void set_player_direction(t_game *game);
void process_door(t_game *game, int *config_count, char *line,
				  int *flags);
void process_anim(t_game *game, int *config_count, char *line,
				  int *flags);
void process_key(t_game *game, int *config_count, char *line,
				 int *flags);

// RayCasting
void init_window(t_game *game);
void define_player_angle(t_game *game);
double normalize_angle(double angle);
void raycasting(t_game *game);
void put_pixel(char *data, int x, int y, int color, int line_length);
void draw_tile(t_game *game, void *mlx, void *win, int x,
			   int y, int size, int color);
int key_hook(int keycode, t_game *game);
int is_move_valid(t_game *game, int new_x, int new_y);
void draw_background(t_game *game);
void draw_player(t_game *game);
void draw_map(t_game *game);
void cast_rays(t_game *game);
void calculate_tile_position(t_game *game);
void draw_map_walls(t_game *game);
void draw_map_bg(t_game *game);
// load textures
void load_textures(t_game *game);
void draw_line(t_game *game, int x0, int y0, int x1, int y1, int color);
long current_millis();

// Texture utilities
int get_texture_color(t_texture *texture, int x, int y);
t_texture *get_wall_texture(t_game *game, int side, int step_x, int step_y);
double get_wall_x(t_game *game, double ray_x, double ray_y, int side);

int key_release(int keycode, t_game *game);
int key_press(int keycode, t_game *game);
int game_loop(void *param);
void	check_count_of_doors(t_game *game);
void change_to_hex(t_game *game);
void add_door(t_game *game, int x, int y, int index);

void update_animation(t_game *game);
void render_animation(t_game *game);
void put_pixels(t_game *game, int x, int y, int color);

#endif
