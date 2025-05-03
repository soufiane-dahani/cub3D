# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sodahani <sodahani@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/03/03 12:11:50 by sodahani          #+#    #+#              #
#    Updated: 2025/05/03 19:02:14 by sodahani         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Compiler and flags
CC = cc
CFLAGS = -Wall -Wextra -Werror 

# Project files
TARGET = cub3D
SRC = cub3d.c libft_used/ft_split.c libft_used/ft_strjoin.c libft_used/ft_strlen.c libft_used/ft_lstadd_back.c libft_used/ft_lstclear.c \
	 libft_used/ft_lstnew.c parsing/malloc.c libft_used/ft_strncmp.c parsing/main.c parsing/map.c libft_used/ft_putstr_fd.c \
	 get_next_line.c get_next_line_utils.c libft_used/ft_atoi.c libft_used/ft_strtrim.c parsing/validate_configuration_lines.c \
	 parsing/extract_number.c parsing/check_xpm.c parsing/map_section.c parsing/validate_configuration_lines2.c

OBJ = $(SRC:.c=.o)

# Rules
all: $(TARGET) banner

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(TARGET)


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

.PHONY: all clean fclean re banner bye