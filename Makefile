# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: alicifer <alicifer@student.42malaga.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/03/25 09:40:38 by alicifer          #+#    #+#              #
#    Updated: 2024/04/18 13:22:14 by alicifer         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = so_long
USER = alicifer

CC = gcc
CFLAGS = -Wextra -Wall -Werror -g
MLX42 = ./MLX42
LIBFT = ./my_libft
SRC_DIR = src/
OBJ_DIR = obj/

SRC_FILES = main map map_checker graphics key_hook free_error

SRC = $(addprefix $(SRC_DIR), $(addsuffix .c, $(SRC_FILES)))
OBJ = $(addprefix $(OBJ_DIR), $(addsuffix .o, $(SRC_FILES)))

OBJF = .cache_exists

all: $(NAME)

$(NAME):	$(OBJ)
			@make all -C $(LIBFT)
			@make -C $(MLX42)
			@$(CC) $(CFLAGS) $(OBJ) -L$(LIBFT) -lft -L$(MLX42) -lmlx42 -framework Cocoa -framework OpenGL -framework IOKit -lglfw -L"/Users/$(USER)/.brew/opt/glfw/lib/" -o $(NAME)
			
$(OBJ_DIR)%.o: $(SRC_DIR)%.c | $(OBJF)
			@$(CC) $(CFLAGS) -c $< -o $@

$(OBJF):
			@mkdir -p $(OBJ_DIR)
			
clean:
			@rm -frf $(OBJ_DIR)
			@make clean -C $(MLX42)
			@make all clean -C 

fclean:
			@rm -rf $(OBJ_DIR)
			@rm -rf $(NAME)
			@make fclean -C $(MLX42)

re: fclean all
			

norm:
			@norminette $(SRC_DIR)
			@norminette $(LIBFT)
						
.PHONY: all clean fclean re norm