
CC = cc
CFLAGS = -Wall -Wextra -Werror

TARGET = cub3D
SRC = raycasting/cub3d.c raycasting/ray_helpers.c raycasting/draw_utils.c libft/ft_split.c libft/ft_strjoin.c libft/ft_strlen.c libft/ft_lstadd_back.c libft/ft_lstclear.c \
	 libft/ft_lstnew.c parsing/malloc.c libft/ft_strncmp.c main.c parsing/map.c libft/ft_putstr_fd.c \
	 libft/get_next_line.c libft/get_next_line_utils.c libft/ft_atoi.c libft/ft_strtrim.c parsing/validate_configuration_lines.c \
	 parsing/extract_number.c parsing/check_xpm.c parsing/map_section.c parsing/validate_configuration_lines2.c parsing/map_section2.c \
	 parsing/validate_configuration_lines3.c parsing/color.c parsing/free.c \
	 raycasting/raycasting_utils.c raycasting/load_textures.c \
	 raycasting/mlx_init.c raycasting/image_utils.c raycasting/key_handler.c \
	 raycasting/map_utils.c  raycasting/movement.c raycasting/doors.c \
	 raycasting/texture_utils.c raycasting/mouse.c raycasting/map_utils2.c


OBJ = $(SRC:.c=.o)
MINILIBX = minilibx-linux/libmlx.a

all: $(TARGET) 

$(TARGET): $(OBJ) $(MINILIBX)
	$(CC) $(CFLAGS) $(OBJ) $(MINILIBX) -o $(TARGET) -lm -lXext -lX11

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJ)

fclean: clean
	rm -rf $(TARGET)

re: fclean all


run:
	./$(TARGET) maps/good/creepy.cub

.PHONY: all clean fclean re run
.SECONDARY: $(OBJ)