/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atucci <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 17:43:02 by atucci            #+#    #+#             */
/*   Updated: 2024/05/21 17:04:54 by atucci           ###   ########.fr       */
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
# include <math.h>
//TODO: delete all printf
# include <stdio.h>
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
/* color for mlx images and library */
/************************************/
# define COLOR_WHITE 0xFFFFFF
# define COLOR_BLACK 0x000000
# define COLOR_RED 0xFF0000
# define COLOR_GREEN 0x00FF00
# define COLOR_BLUE 0x0000FF
# define COLOR_YELLOW 0xFFFF00
# define COLOR_MAGENTA 0xFF00FF
# define COLOR_CYAN 0x00FFFF

/*TODO:ADDITIONAL STRUCTS
* Ray Struct: Represents a ray in the scene.
* Intersection Struct: Represents the result of a ray-object intersection
* Material Struct: Represents the material properties of objects
*/
typedef struct s_color
{
	int	r;
	int	g;
	int	b;
}	t_color;

/*typedef struct s_pixel
{
	int	x;
	int	y;
}	t_pixel;

typedef struct s_point2d
{
	double	x;
	double	y;
}	t_point2d;
*/

//TODO: small update with the 'w'
typedef struct s_vector
{
	double	x;
	double	y;
	double	z;
	double	w;
}	t_vector;

typedef struct s_amb_light
{
	char	*identifier;
	double	ratio;
	t_color	color;
}	t_amb_light;

typedef struct s_camera
{
	char		*identifier;
	t_vector	viewpoint;
	t_vector	orientation;
	int			fov;
}	t_camera;

typedef struct s_light
{
	char		*identifier;
	t_vector	position;
	double		brightness;
	t_color		color;
}	t_light;

typedef struct s_sphere
{
	char		*identifier;
	t_vector	center;
	double		diameter;
	t_color		color;
}	t_sphere;

typedef struct s_plane
{
	char		*identifier;
	t_vector	point;
	t_vector	normal;
	t_color		color;
}	t_plane;

typedef struct s_cylinder
{
	char		*identifier;
	t_vector	center;
	t_vector	axis;
	double		diameter;
	double		height;
	t_color		color;
}	t_cylinder;

typedef struct s_setting
{
	t_amb_light		*amb_light;
	t_camera		*camera;
	t_light			**lights;
	int				num_lights;
	t_sphere		**spheres;
	int				num_spheres;
	t_plane			**planes;
	int				num_planes;
	t_cylinder		**cylinders;
	int				num_cylinders;
	int				num_cones;
}	t_setting;

/**********************************************************************/
/* Define the struct to use for managing windows, image a other stuff */
/**********************************************************************/
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

int			parsing_map(char *map, t_setting *set);
void		create_setting(char **line, t_setting *set);
void		count_elements(char **details, t_setting *set);
void		setback_zero(t_setting *set);
void		alloc_struct_elem(t_setting *setting);
/***************************************************/
/*Those function are going to start the struct     */
/***************************************************/
void		start_amb_light(t_setting *set, char **details);
void		start_camera(t_setting *set, char **details);
void		start_lights(t_setting *set, char **details);
void		start_cylinder(t_setting *set, char **details);
void		start_spheres(t_setting *set, char **details);
void		start_planes(t_setting *set, char **details);
void		start_cones(t_setting *set, char **details);

/***************************************************/
/*Those function are going to parse the numbers    */
/***************************************************/
t_color		parse_color(char *str);
t_vector	parse_vector(char *str);
void		print_color(t_color color);
void		print_vector(t_vector vector);
/***************************************************/
/*Those function are going to add elem to arrays   */
/***************************************************/
void		add_light_to_array(t_light *to_add, t_setting *set);
void		add_plane_to_array(t_plane *to_add, t_setting *set);
void		add_sphere_to_array(t_sphere *to_add, t_setting *set);
void		add_cylinder_to_array(t_cylinder *to_add, t_setting *set);

/************************/
/*   Math and vectors   */
/************************/
double		dot(t_vector v1, t_vector v2);
t_vector	subtract(t_vector v1, t_vector v2);
int	create_trgb(t_color color);
/************************/
/*freeing the function  */
/************************/
void	free_struct(t_setting *set);
/************************/
/* print debug function */
/************************/
void	struct_full_status(t_setting *set);
void	struct_status(t_setting *set);
/******************/
/* utils function */
/******************/
void	error_msg(char *str);
int		my_strcmp(const char *str1, const char *str2);
double	my_atof(const char *str);
int		check_null_array(char **array);
void	print_string_array(char **array);
int		free_string_array(char **array);
int		lenght_string_array(char **array);
void	remove_new_line(char **matrix, char replacement, char to_replace);
void	replace_me(char *str, char replacement, char to_replace);
/*********************************/
/* useful function to manage mlx */
/*********************************/
void	manage_mlx(t_mlx *obj, t_setting *set);
int		window_close(void *param);
void	my_mlx_pixel_put(t_mlx *data, int x, int y, int color);
#endif
