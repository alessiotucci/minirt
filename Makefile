# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: atucci <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/04/26 17:46:19 by atucci            #+#    #+#              #
#    Updated: 2024/05/01 15:16:29 by atucci           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# *********************************
# setting up the name of the exec *
# *********************************
NAME = miniRT

# *************************************************
# setting up the variable that will be the source *
# *************************************************
SOURCE = ./main.c \
		 ./manage_mlx.c \
		 ./parsing_map.c \
		 ./utils.c \
		 ./translations.c \
		 ./rotations.c \
		 ./scaling.c \

HEADERS = ./minirt.h \

# ***********************************************************
# setting up the flag that will be used for the compilation *
# ***********************************************************
FLAG = -Wall -Wextra -Werror -O3


# ***************************************************************
# setting up the compiler that will be used for the compilation *
# ***************************************************************
CC = gcc

#********************************************************
# This variable specifies the path to the libft library *
#********************************************************
LIBFT = libft/libft.a

#**********************
# this is for mlx_dir *
#**********************
MLX_DIR = ./mlx

#***************************************
# Define the flags for the mlx library *
#***************************************
MLXFLAG = -L$(MLX_DIR) -lmlx -L/usr/lib -lXext -lX11 -lm -lz

INCLUDES = -I/usr/include -I$(MLX_DIR)

#************************************************************************
#https://harm-smits.github.io/42docs/libs/minilibx/getting_started.html *
#************************************************************************
#MLX = ./mlx/libmlx.a
#MLX = ./mlx/libmlx_Linux.a

# ***************************************************************
# using the implicit rules of makefile, we will create the objs *
# it is called "substitution reference"                         *
# ***************************************************************
OBJ = $(SOURCE:.c=.o)

# **************************************************************************** #
# Color codes for echo commands to make the output more visually informative.  #
# **************************************************************************** #
GREEN := \033[1;32m
CYAN := \033[1;36m
YELLOW := \033[1;33m
RED := \033[1;31m
RESET := \033[0m

# ****************
# Default target *
# ****************
all: $(NAME)

# *******************************
# Rule for building the program *
# *******************************
$(NAME): $(OBJ)
	@echo "$(GREEN)Compiling libft...$(RESET)\n"
	$(MAKE) -C libft
	@echo "$(GREEN)Compiling mlx...$(RESET)\n"
	$(MAKE) -C mlx
	@echo "$(GREEN)Linking...$(RESET)\n"
	$(CC) $(FLAG) $(OBJ) $(LIBFT) $(MLXFLAG) -o $(NAME)
	@echo "$(GREEN)Done!\n$(RESET)"

%.o: %.c
	@echo "$(CYAN)Compiling $<...$(RESET)"
	$(CC) $(FLAG) $(INCLUDES) -c $< -o $@
	@echo "$(CYAN)Done compiling $<.$(RESET)\n"


# ****************************************
#  Rule for cleaning up the object files *
# ****************************************
clean:
	@echo "$(YELLOW)Cleaning up object files...$(RESET)"
	$(MAKE) -C libft clean
	$(MAKE) -C mlx clean
	rm -f $(OBJ)
	@echo "$(YELLOW)Done!\n$(RESET)"

# *******************************************************
# Rule for cleaning up the object files and the program *
# *******************************************************
fclean: clean
	@echo "$(RED)Removing executable...$(RESET)"
	$(MAKE) -C libft fclean
	rm -f $(NAME)
	@echo "$(RED)Done!\n$(RESET)"

# **********************************
# Rule for recompiling the program *
# **********************************
re: fclean all

#*********************************************
# .PHONY targets to specify non-file targets *
#*********************************************
.PHONY: all clean fclean re


#***********************************************
# Rule for deleting the hidden files generated *
#***********************************************
hidden:
	@echo "$(YELLOW) Listing hidden files:"
	@find . \( -name ".DS_Store" -o -name ".*.swp" -o -name ".*.swo" -o -name "a.out" \) -type f -print
	@echo "$(RESET)$(RED) Deleting hidden files: $(RESET)"
	@find . \( -name ".DS_Store" -o -name ".*.swp" -o -name ".*.swo" -o -name "a.out" \) -type f -delete


#***********************************************************************
# Download and install the MLX library if it is not already installed. *
#***********************************************************************
mlx:
	if [ -e $(MLX_DIR) ]; \
	then \
	echo "MiniLibX's directory detected"; \
	else \
	git clone git@github.com:42Paris/minilibx-linux.git \
	&& mv minilibx-linux mlx; fi
