# Compiler and flags
CC = cc
CFLAGS =  -Iincludes -g3 #-Wall -Wextra -Werror

# Project files
TARGET = cub3D
SRC = raycasting/cub3d.c libft/ft_split.c libft/ft_strjoin.c libft/ft_strlen.c libft/ft_lstadd_back.c libft/ft_lstclear.c \
	 libft/ft_lstnew.c parsing/malloc.c libft/ft_strncmp.c main.c parsing/map.c libft/ft_putstr_fd.c \
	 libft/get_next_line.c libft/get_next_line_utils.c libft/ft_atoi.c libft/ft_strtrim.c parsing/validate_configuration_lines.c \
	 parsing/extract_number.c parsing/check_xpm.c parsing/map_section.c parsing/validate_configuration_lines2.c parsing/map_section2.c \
	 parsing/validate_configuration_lines3.c \
	 raycasting/raycasting_utils.c raycasting/load_textures.c \
	 raycasting/mlx_init.c raycasting/image_utils.c raycasting/key_handler.c \
	 raycasting/map_utils.c  raycasting/movement.c \


OBJ = $(SRC:.c=.o)
MINILIBX = minilibx-linux/libmlx.a

# Rules
all: $(TARGET) banner clean

$(TARGET): $(OBJ) $(MINILIBX)
	$(CC) $(CFLAGS) $(OBJ) $(MINILIBX) -o $(TARGET) -lm -lXext -lX11

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJ)

fclean: clean bye
	rm -rf $(TARGET)

re: fclean all


banner:
	@echo "\033[1;32m                                             \033[0m"
	@echo "\033[1;32m                                             \033[0m"
	@echo "\033[1;34m  		  ██████╗██╗   ██╗██████╗  ██████╗ ██████╗  \033[0m"
	@echo "\033[1;34m 		 ██╔════╝██║   ██║██╔══██╗ ╚═══██╗██╔══██╗ \033[0m"
	@echo "\033[1;34m 		 ██║     ██║   ██║██████╔╝  ████╔╝██║  ██║ \033[0m"
	@echo "\033[1;34m 		 ██║     ██║   ██║██╔══██╗  ╚══██╗██║  ██║ \033[0m"
	@echo "\033[1;34m 		 ╚██████╗╚██████╔╝██████╔╝ ██████╔╝██████╔╝ \033[0m"
	@echo "\033[1;34m  		 ╚═════╝ ╚═════╝ ╚═════╝  ╚═════╝ ╚═════╝  \033[0m"
	@echo "\033[1;32m                                             \033[0m"
	@echo "\033[1;32m    		        🕹️  Welcome to Cub3D! 🕹️          \033[0m"
	@echo "\033[1;32m       		                                      \033[0m"
	@echo "\033[1;32m         		                                    \033[0m"

bye:
	@echo "\033[1;32m	                                                                  \033[0m"
	@echo "\033[1;32m	                                                                  \033[0m"
	@echo "\033[1;31m	   ██████╗  ██████╗  ██████╗ ██████╗ 	██████╗ ██╗   ██╗███████╗██╗ \033[0m"
	@echo "\033[1;31m	  ██╔════╝ ██╔═══██╗██╔═══██╗██╔══██╗	██╔══██╗╚██╗ ██╔╝██╔════╝██║ \033[0m"
	@echo "\033[1;31m	  ██║  ███╗██║   ██║██║   ██║██║  ██║	██████╔╝ ╚████╔╝ █████╗  ██║ \033[0m"
	@echo "\033[1;31m	  ██║   ██║██║   ██║██║   ██║██║  ██║	██╔══██╗  ╚██╔╝  ██╔══╝  ╚═╝ \033[0m"
	@echo "\033[1;31m	  ╚██████╔╝╚██████╔╝╚██████╔╝██████╔╝	██████╔╝   ██║   ███████╗██╗ \033[0m"
	@echo "\033[1;31m	   ╚═════╝  ╚═════╝  ╚═════╝ ╚═════╝ 	╚═════╝    ╚═╝   ╚══════╝╚═╝ \033[0m"
	@echo "\033[1;32m	                                                                  \033[0m"
	@echo "\033[1;32m	                      See you next time!                          \033[0m"
	@echo "\033[1;32m                                               					   \033[0m"
	@echo "\033[1;32m	                                                                  \033[0m"

run:
	./$(TARGET) maps/good/creepy.cub

.PHONY: all clean fclean re banner bye run
.SECONDARY: $(OBJ)