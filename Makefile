# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: atucci <atucci@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/04/26 17:46:19 by atucci            #+#    #+#              #
#    Updated: 2025/02/27 15:15:55 by atucci           ###   ########.fr        #
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
		 ./main_utils.c \
		 ./manage_mlx.c \
		 ./mlx_utils.c \
		 ./freeing.c \
		 ./freeing2.c \
		 ./draw_scene.c \
		 ./centering.c \
		 ./selection_status.c \
		 ./validation/validation.c \
		 ./validation/validation_utils.c \
		 ./validation/validation_extra.c \
		 ./normal.c \
		 ./create_setting.c \
		 ./add_elem_array.c \
		 ./parsing/parsing_map.c \
		 ./parsing/parsing_numbers.c \
		 ./starting/start_shapes.c \
		 ./starting/start_scenes.c \
		 ./extra/utils.c \
		 ./extra/print_debug.c \
		 ./extra/print_debug2.c \
		 ./extra/print_single.c \
		 ./extra/my_atof.c \
		 ./extra/comparing.c \
		 ./extra/replace_me.c \
		 ./extra/type_string.c \
		 ./transformations/translations.c \
		 ./transformations/rotations.c \
		 ./transformations/matrix_rotations.c \
		 ./transformations/scaling.c \
		 ./transformations/shearing.c \
		 ./shapes/plane.c \
		 ./shapes/sphere.c \
		 ./shapes/cylinder.c \
		 ./bonus/cone.c \
		 ./vector/vector_operations.c \
		 ./vector/utils_vectors.c \
		 ./vector/complex_operations.c \
		 ./colors/clamp.c \
		 ./colors/colors.c \
		 ./colors/operation_color.c \
		 ./colors/converting_color.c \
		 ./matrix/matrix_utils.c \
		 ./matrix/initialize_matrix.c \
		 ./matrix/operations_matrix.c \
		 ./matrix/determinant.c \
		 ./matrix/inversing.c \
		 ./matrix/void.c \
		 ./matrix/submatrix.c \
		 ./raycasting/create_ray.c \
		 ./raycasting/intersection_ray.c \
		 ./raycasting/utils_obj.c \
		 ./raycasting/hit.c \
		 ./raycasting/transformation_ray.c \
		 ./raycasting/cast_ray.c \
		 ./raycasting/cast_ray_helper.c \
		 ./intersection/intersection.c \
		 ./intersection/old_list.c \
		 ./intersection/intersection_list.c \
		 ./intersection/intersection_sphere.c \
		 ./intersection/intersection_plane.c \
		 ./intersection/intersection_cylinder.c \
		 ./intersection/cylinder_utils.c \
		 ./intersection/sort_intersection.c \
		 ./intersection/copy_simple_field.c \
		 ./shadows/lighting.c \
		 ./shadows/material.c \
		 ./shadows/lambert_reflection_model.c \
		 ./shadows/phong_reflection_model.c \
		 ./shadows/is_shadowed.c \
		 ./default_setting.c \
		 ./computation.c \
		 ./rendering/key_pressed.c \
		 ./rendering/rendering_utils.c \
		 ./rendering/change_diameter.c \
		 ./rendering/mouse_select.c \
		 ./rendering/rotation_handlers.c \
		 ./rendering/translation_handlers.c \
		 ./selected_obj.c \


HEADERS = ./minirt.h \

# ***********************************************************
# setting up the flag that will be used for the compilation *
# ***********************************************************
FLAG = -Wall -Wextra -Werror -O3 -gdwarf-4

# -gdwarf-4

# ***************************************************************
# setting up the compiler that will be used for the compilation *
# ***************************************************************
CC = cc

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

# *****************************************************************************
# UNIT TEST: this rules allow me to compile the whole project and test        *
# single functions, I use a main inside the function and exclude the main     *
# *****************************************************************************
TEST_SOURCE = $(filter-out ./main.c, $(SOURCE))
TEST_OBJ = $(TEST_SOURCE:.c=.o)

test: $(TEST_OBJ)
	@echo "$(RED)Compiling libft...$(RESET)\n"
	$(MAKE) -C libft
	@echo "$(RED)Compiling mlx...$(RESET)\n"
	$(MAKE) -C mlx
	@echo "$(RED)Linking...$(RESET)\n"
	$(CC) $(FLAG) $(TEST_OBJ) $(LIBFT) $(MLXFLAG) -o test
	@echo "$(YELLOW)Done!\n$(RESET)"

clean_test: fclean
	@echo "removing test\t"
	rm -f test
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
#*****************************************************************************
# Download and install the MLX library if it is not already installed.
#*****************************************************************************
mlx:
	@if [ -e $(MLX_DIR) ]; then \
		echo "$(GREEN)MiniLibX directory detected.$(RESET)"; \
	else \
		echo "$(YELLOW)Cloning MiniLibX repository...$(RESET)"; \
		git clone git@github.com:42Paris/minilibx-linux.git; \
		mv minilibx-linux mlx; \
		echo "$(GREEN)MiniLibX has been successfully cloned.$(RESET)"; \
	fi


clean_mlx:
	@echo "$(RED)Deleting mlx to norm check $(RESET)"
	rm -rf $(MLX_DIR)

norminette: clean_mlx
	@echo "$(GREEN) Running norminette without mlx $(RESET)"
	@norminette
	@make mlx
