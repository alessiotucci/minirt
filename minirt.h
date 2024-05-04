/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atucci <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 17:43:02 by atucci            #+#    #+#             */
/*   Updated: 2024/05/04 15:07:27 by atucci           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include "mlx/mlx.h"
# include "libft/libft.h"

/***********************************************************************/
/*The open and creat functions are declared in the header file fcntl.h */
/* while close is declared in unistd.h.                               */
/*https://www.gnu.org/software/libc/manual/html_node                   */
/***********************************************************************/
# include <fcntl.h>
# include <unistd.h>

/************************/
/* Define keyboard code */ //TODO: check with Ubuntu codes
/************************/
# define ARROW_LEFT 123
# define ARROW_RIGHT 124
# define ARROW_DOWN 125
# define ARROW_UP 126
# define MINUS 27
# define PLUS 24
# define SPACE 49
# define KEY_R 15
# define ESCAPE 53

//TODO: CHECK UBUNTU CODES
# define LEFT 65361
# define RIGHT 65363
# define W 119
# define A 97
# define S 115
# define D 100
# define ESC 65307
# define NORTH_SOUTH 0
# define EAST_WEST 1

/* Define color macros */
# define BLUE    "\033[1;34m"
# define PURPLE  "\033[1;35m"
# define GRAY    "\033[1;30m"
# define GREEN   "\033[1;32m"
# define CYAN    "\033[1;36m"
# define YELLOW  "\033[1;33m"
# define RED     "\033[1;31m"
# define RESET   "\033[0m"
/* Define Background colors macros */
# define BG_RESET        "\033[49m"
# define BG_GREEN        "\033[42m"
# define BG_CYAN         "\033[46m"
# define BG_YELLOW       "\033[43m"
# define BG_RED          "\033[41m"

/***************************************/
/* Define default size for the windows */
/***************************************/
# define DEFAULT_WIDTH 1280
# define DEFAULT_HEIGHT 720

/************************************/
/* color for printing on the screen */
/************************************/
# define COLOR_WHITE 0xFFFFFF
# define COLOR_BLACK 0x000000
# define COLOR_RED 0xFF0000
# define COLOR_GREEN 0x00FF00
# define COLOR_BLUE 0x0000FF
# define COLOR_YELLOW 0xFFFF00
# define COLOR_MAGENTA 0xFF00FF
# define COLOR_CYAN 0x00FFFF
/* Define the struct to use for managing windows, image a other stuff */
typedef struct s_mlx
{
	char		*map_name;
	int			width;
	int			height;
	void		*mlx;
	void		*win;
	void		*img_pointer;
	int			bits;
	int			lsize;
	int			endian;
	char		*img_string;
}		t_mlx;

int		parsing_map(char *map);
/******************/
/* utils function */
/******************/
void	error_msg(char *str);
int		my_strcmp(const char *str1, const char *str2);
int		check_null_array(char **array);
void	print_string_array(char **array);
int		free_string_array(char **array);
int		lenght_string_array(char **array);
/* useful function to manage mlx */
void	manage_mlx(t_mlx *obj);
int		window_close(void *param);
#endif
