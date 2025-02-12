/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atucci <atucci@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 17:43:02 by atucci            #+#    #+#             */
/*   Updated: 2025/02/12 16:48:37 by atucci           ###   ########.fr       */
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
# define ARROW_LEFT 65361
# define ARROW_RIGHT 65363
# define ARROW_DOWN 65364
# define ARROW_UP 65362
# define MINUS 61
# define PLUS 45
# define SPACE 49
# define KEY_R 15
# define ESCAPE 53

# define KEY_X 120
# define KEY_Y 121
# define KEY_Z 122
# define KEY_Q 113
# define KEY_W 119
# define KEY_E 101

//TODO: CHECK UBUNTU CODES
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

/******************************************************************************/
/*History of Screen Resolutions                                               */
/*Screen resolutions have come a long way since the early days of computing.  */
/*In the 1970s, the standard screen resolution was 320×200 pixels.            */
/*In the 1980s, resolutions increased, with 640×480 becoming the new standard.*/
/*In the 1990s, resolutions increased, with 1024×768 becoming the new standard*/
/*In the 2000s, resolutions increased even more, with 1920×1080              .*/
/******************************************************************************/
/***************************************/
/* Define default size for the windows */
/***************************************/
# define DEFAULT_WIDTH 205
# define DEFAULT_HEIGHT 90

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

/***************************************/
/* defining this for comparing doubles */
/***************************************/
# define EPSILON 0.00001
# define EPSILON_v2 1e-6

/*TODO:ADDITIONAL STRUCTS
* Ray Struct: Represents a ray in the scene.
* Intersection Struct: Represents the result of a ray-object intersection
* Material Struct: Represents the material properties of objects:TODO BONUS!
*/
typedef struct s_color
{
	double	r;
	double	g;
	double	b;
}	t_color;

typedef struct s_material
{
	t_color	color;// material can get color from the shape
	double	ambient;
	double	diffuse;
	double	specular;
	double	shininess;

}	t_material;

//TODO: small update with the 'w'
typedef struct s_vector
{
	double	x;
	double	y;
	double	z;
	double	w;
}	t_vector;

typedef struct s_ray
{
	t_vector	origin;
	t_vector	direction;
}	t_ray;

// Define the enum for the object types
typedef enum e_type
{
	T_CAMERA,
	T_LIGHT,
	T_SPHERE,
	T_PLANE,
	T_CYLINDER,
	T_NULL
}	t_type;

// Define the struct that will hold the object type and the void pointer
typedef struct s_object
{
	t_type	type;
	void	*address; //TODO: maybe should free it/
	void	*original_addr;   // NEW: pointer to the original object.
}	t_object;

/* let's see if it is usefult ***********************************************/
//TODO:
typedef struct s_intersection
{
	double	t;
	t_object	obj;
}	t_intersection;


/*
typedef struct s_intersection_list
{
	t_intersection	*intersections;
	int count;
}	t_intersection_list;
*/

/**/
//TODO: NEW LINKED_LIST!
/**/
typedef struct s_list_intersect
{
	t_intersection			*intersection;
	struct s_list_intersect	*next;
}	t_list_intersect;
/*****************************************************************************/

/*****************************************************************************/
/* This computation was missing from the previously implementations          */
/*****************************************************************************/
typedef struct s_computations
{
    double     t;         // The parameter t at which the intersection occurs.
    t_object   object;    // The object that was hit.
    t_vector   point;     // The actual hit point on the surface.
    t_vector   over_point;// The hit point slightly offset along the normal.
    t_vector   eyev;      // The eye vector (pointing toward the camera).
    t_vector   normalv;   // The surface normal at the hit point.
    // You can add more fields if needed, for example:
    t_material material; // Material properties at the hit point.
}   t_computations;
/*****************************************************************************/
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
	double		image_plane_height;
	double		image_plane_width;
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
	double		**transform;
	t_material	material;//THIS IS LAST CHANGE

}	t_sphere;

typedef struct s_plane
{
	char		*identifier;
	t_vector	point;
	t_vector	normal;
	t_color		color;
	double		**transform;
	t_material	material;//THIS IS LAST CHANGE
}	t_plane;

typedef struct s_cylinder
{
	char		*identifier;
	t_vector	center;
	t_vector	axis;
	double		diameter;
	double		height;
	double		min;
	double		max;
	int			closed;
	t_color		color;
	double		**transform;
	t_material	material;//THIS IS LAST CHANGE
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
	t_object	*selected_object;  // Pointer to the currently selected object (if any)
	t_setting 	*setting;
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
t_vector	parse_vector(char *str, double flag);
void		print_color(t_color color);
void		print_vector(t_vector vector);
/***************************************************/
/*Those function are going to add elem to arrays   */
/***************************************************/
void		add_light_to_array(t_light *to_add, t_setting *set);
void		add_plane_to_array(t_plane *to_add, t_setting *set);
void		add_sphere_to_array(t_sphere *to_add, t_setting *set);
void		add_cylinder_to_array(t_cylinder *to_add, t_setting *set);

/***********************/
/*Where are the colors?*/
/***********************/
int			create_trgb(t_color color);
double			my_clamp(double value, double min_val, double max_val);
/**********************/
/*Colors/converting.c */
/**********************/
double		convert_component(double component);
t_color		convert_color(t_color old);
double		convert_component_inverse(double component);
t_color		convert_color_inverse(t_color color);

/****************************/
/* Colors/operation_color.c */
/****************************/
t_color		add_colors(t_color c1, t_color c2);
t_color		subtract_colors(t_color c1, t_color c2);
t_color		multiply_color_by_scalar(t_color c, float scalar);
t_color		multiply_colors(t_color c1, t_color c2);
t_color		create_color(double r, double g, double b);
/******************************/
/* Comparing is not that easy */
/******************************/
int			comparing_vector(t_vector a, t_vector b);
int			comparing_double(double a, double b);
int			is_a_point(t_vector vect);
int			is_a_vector(t_vector vect);
t_vector	negate(t_vector vect);
t_vector	create_point(double x, double y, double z);
t_vector	create_vector(double x, double y, double z);
/********************/
/* Math and vectors */
/********************/
t_vector	add(t_vector v1, t_vector v2);
t_vector	subtract(t_vector v1, t_vector v2);
t_vector	multiplication(t_vector v, double scalar);
t_vector	division(t_vector v, double scalar);
/**********************/
/* Complex operations */
/**********************/
t_vector	normalization(t_vector vector);
double		magnitude(t_vector vector);
double		dot(t_vector v1, t_vector v2);
t_vector	cross(t_vector v1, t_vector v2);

/*********************/
/* Matrix operations */
/*********************/
void		free_heap_matrix(double **matrix, int rows);
double		**malloc_matrix(int rows, int col);
void		init_matrix(int rows, int cols, double matrix[rows][cols]);
void		init_heap_matrix(int rows, int cols, double **matrix);
void		print_int_matrix(int rows, int cols, double **matrix);
/******************************/
/*prolly will need some more */
/******************************/
void		copy_row_value(double destination[4], double source[4]);
double		**value_matrix(double a[4], double b[4], double c[4], double d[4]);
double		**copy_matrix(int rows, int cols, double **source);
/*************************/
/* matrix operations pt 2*/
/*************************/
int			comparing_heap_matrix(int rows, int cols, double **a, double **b);
double		**multiply_matrix(int cols_a, int rows_b, double **a, double **b);
t_vector	matrix_x_vector(double **a, t_vector b);
void		create_identity_matrix(double	**ret);
double		**transposing(int rows, int cols, double **matrix);
/*********************/
// othe 2            */
/*********************/
double		determinant(double **matrix, int size);
double		determinant_two(double **matrix);
double		determinant_n(double **matrix, int size);
double		minor(int row, int col, double **matrix, int size);
double		cofactor(int row, int col, double **matrix, int size);
double		**submatrix(int index_rows, int index_cols, double **matrix, int size);
/*********************/
/*                   */
/*********************/
int		is_matrix_invertible(int size, double **matrix);
double	**matrix_of_cofactors(int size, double **matrix);
double	**divide_matrix(int size, double **source, double det);
double	**inversing_matrix(int size, double **source);

/**************************/
/* VOID! check this stuff */
/**************************/
void	divide_matrix_void(int size, double **source, double det);
void	matrix_of_cofactors_void(int size, double **matrix, double **n);
void	transposing_void(int rows, int cols, double **matrix);
void	inversing_matrix_void(int size, double **source);

//TODO: The transformation need to return matrix sometimes!
/**********************************/
/* Transformations/translations.c */
/**********************************/
t_vector	translations(t_vector move, t_vector origin);
double		**create_translation_matrix(t_vector move);
t_vector	inverse_translations(t_vector move, t_vector origin);
/*****************************/
/* Transformations/scaling.c */
/*****************************/
void		identity_value_matrix(double **matrix, t_vector source);
t_vector	scaling(t_vector move, t_vector origin);
double		**create_scaling_matrix(t_vector move);
t_vector	scaling_inverse(t_vector move, t_vector origin);
/*******************************/
/* Transformations/rotations.c */
/*******************************/
t_vector	rotation_x(t_vector origin, double radians);
t_vector	rotation_y(t_vector origin, double radians);
t_vector	rotation_z(t_vector origin, double radians);
/**************************************/
/* Transformations/matrix_rotations.c */
/**************************************/
double		**matrix_rotation_x(double radians);
double		**matrix_rotation_y(double radians);
double		**matrix_rotation_z(double radians);

/******************************/
/* Transformations/shearing.c */
/******************************/
t_vector	shearing(t_vector origin, double value[6]);

/***************************/
/* Raycasting/create_ray.c */
/***************************/
t_ray		create_ray(t_vector origin, t_vector direction);
void		print_ray(t_ray ray);
t_vector	position_ray(t_ray ray, double t);

/********************/
/* Raycasting/hit.c */
/********************/
t_intersection	*hit_v2(t_list_intersect *list);

/*************************/
/* Raycasting/cast_ray.c */
/*************************/
t_ray	create_ray_from_camera(t_mlx *data, int x, int y);
void	cast_rays(t_mlx *data);

/********************************/
/* Raycasting/cast_ray_helper.c */
/********************************/
void	each_pixel_calculation(t_mlx *data, int x, int y);
void	each_pixel_calculationV2(t_mlx *data, int x, int y);

/*********************************/
/* Raycasting/intersection_ray.c */
/*********************************/
t_vector	get_sphere_to_ray(t_sphere sphere, t_ray ray);
double	get_discriminant(t_vector sphere_to_ray, t_ray ray, double diameter);
//TODO: v2
//t_intersection_list	*intersect_sphere(t_sphere sphere, t_ray ray);
t_list_intersect *intersect_sphere(t_sphere *sphere, t_ray old_ray);

/***********************************/
/* Raycasting/transformation_ray.c */
/***********************************/
t_ray	transform_ray(t_ray original, double **matrix);
void	set_sphere_transformations(t_sphere *sphere, double **new);

/*******************/
/* shapes/sphear.c */
/*******************/
t_sphere	create_sphere(char *id, t_vector center, double d, t_color c);
int			calculate_sphere_color(t_intersection *intersection);
/************************/
/*freeing the function  */
/************************/
void		free_struct(t_setting *set);
void		free_single_sphere(t_sphere *sphere);
void		free_single_plane(t_plane *plane);
void		free_single_cylinder(t_cylinder *cylinder);
/************************/
/* print debug function */
/************************/
void		struct_full_status(t_setting *set);
void		struct_status(t_setting *set);
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
void	manage_mlx(t_mlx *obj);
int		window_close(void *param);
void	my_mlx_pixel_put(t_mlx *data, int x, int y, int color);
void	my_new_image(t_mlx *data);

void	send_to_centre(t_setting *set); //prima
//TODO:delete this WE DONT NEED TO to center the sphere
void center_sphere(t_sphere *sphere, int window_width, int window_height);

int		mouse_click(int button, int x, int y, t_mlx *mlx);//seconda
/********************************************************/
/* started to create complex obj to track intersections */
/********************************************************/
void				print_intersection(t_intersection i);
//void				print_intersection_list(t_intersection_list *lis);
int					print_type(t_object obj);
void				print_single_sphere(t_sphere *one_sphere);
void				print_single_cylinder(t_cylinder *one_cylinder);
void				print_single_plane(t_plane *one_plane);

/*******************************/
/* intersection/intersection.c */
/*******************************/
t_type				string_to_type(char *type);
t_object			create_object(char *type, void *object);
t_intersection		intersection(double t, char *type, void *object);
void				free_intersection(t_intersection *intersect);


//TODO

void	concatenate_lists(t_list_intersect **list1, t_list_intersect *list2);
/************************************/
/* intersection/intersection_list.c */
/************************************/
t_list_intersect	*create_new_node(t_intersection *intersection);
void	add_intersection_l(t_list_intersect **head, t_intersection *intersection);
void	free_list(t_list_intersect **head);
void	print_list(t_list_intersect **head, int debug);

/************************************/
/* intersection/sort_intersection.c */
/************************************/
void	insert_sorted(t_list_intersect **sorted, t_list_intersect *new);
void	sort_intersection_list(t_list_intersect **head);

/***************************/
/* draw_scene/draw_scene.c */
/***************************/
void				draw_scene(t_mlx *data);

/************/
/* normal.c */
/************/
t_vector	reflect(t_vector in, t_vector normal);
t_vector	normal_at(t_sphere sphere, t_vector world_point);
//TODO
//t_vector v2normal_at(t_object obj, t_vector world_point);
t_vector v2normal_at(t_object obj, t_vector world_point, t_ray r);
t_vector normal_at_sphere(t_sphere *sphere, t_vector world_point);

//TODO
void	print_single_light(t_light *one_light);
/**********************/
/* Shadows/material.c */
/**********************/
//t_material			material(void);
void		print_material(t_material mat);
t_material	material(t_color color);
/**********************/
/* Shadows/lighting.c */
/**********************/
//TODO norminetted!!
/*
t_color	phong_lighting(t_material mat, t_light light, t_vector point, t_vector eye, t_vector normal);
t_color	phong_lightingV2(t_setting *world, t_computations comps, t_light light);
t_color	lambert_formula(t_intersection *i, t_light light, t_vector point, t_vector normal, t_setting *world);
*/

//TODO; planes!
t_list_intersect	*intersect_plane(t_plane *plane, t_ray old_ray);

t_color	get_color_intersect(t_object obj);
int	is_shadowed(t_setting *world, t_vector point, t_light light);

//TODO: after graduations
t_cylinder	create_cylinder(char *id, t_vector center, double d, t_color c);
t_list_intersect	*intersect_cylinder(t_cylinder *cylinder, t_ray old_ray);
void	set_cylinder_size(t_cylinder *cylinder, double min, double max);
void	set_cylinder_cap(t_cylinder *cylinder);
//Fixing leaks with ftroise
void	my_free_setting(t_setting *set);
//TODO: after coming back from China (fix compilation issues)
t_vector	default_vector(void);
t_color	default_color(void);
//TODO: reasoning by GPT3
t_computations prepare_computations(t_intersection i, t_ray r);

t_color	lambert_lighting(t_setting *world, t_computations comps, t_light light);
t_color	phong_lighting(t_setting *world, t_computations comps, t_light light);
t_color	shade_hit(t_setting *world, t_computations comps, int flag);
t_color	my_shade_hit(t_setting *world, t_computations comps, t_intersection *c_i);

/*************************/
/*Experimenting with mlx */
/*************************/
int	key_pressed_gpt(int keycode, void *param);
void	clean_close(t_mlx *project);
void	camera_image_plane(t_mlx *mlx);
int	cast_mouse_ray(int x, int y, t_mlx *mlx, t_setting *world);


t_list_intersect	*intersect_world(t_setting *world, t_ray ray);

/********************/
/*Rotation handlers */
/********************/
void	handle_x_rotation(t_mlx *data, int direction);
void	handle_y_rotation(t_mlx *data, int direction);
void	handle_z_rotation(t_mlx *data, int direction);

void change_size(t_object *obj, int flag);
char	*type_to_string(t_type type);
#endif
