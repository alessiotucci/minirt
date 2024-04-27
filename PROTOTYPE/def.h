/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   def.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atucci <atucci@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 15:27:38 by atucci            #+#    #+#             */
/*   Updated: 2024/04/27 15:32:43 by atucci           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

typedef struct s_color
{
	int	r;
	int	g;
	int	b;
}	t_color;

typedef struct s_vector
{
	double	x;
	double	y;
	double	z;
}	t_vector;

typedef struct s_ambient_light
{
	char	identifier;
	double	ratio;
	t_color	color;
}	t_ambient_light;

typedef struct s_camera
{
	char		identifier;
	t_vector	viewpoint;
	t_vector	orientation;
	int			fov;
}	t_camera;

typedef struct s_light
{
	char		identifier;
	t_vector	position;
	double		brightness;
	t_color		color;
}	t_light;

typedef struct s_sphere
{
	char		identifier;
	t_vector	center;
	double		diameter;
	t_color		color;
}	t_sphere;

typedef struct s_plane
{
	char		identifier;
	t_vector	point;
	t_vector	normal;
	t_color		color;
}	t_plane;

typedef struct s_cylinder
{
	char		identifier;
	t_vector	center;
	t_vector	axis;
	double		diameter;
	double		height;
	t_color		color;
}	t_cylinder;

typedef struct s_setting
{
	t_ambient_light	*ambient_light;
	t_camera		*camera;
	t_light			**lights;
	int				num_lights;
	t_sphere		**spheres;
	int				num_spheres;
	t_plane			**planes;
	int				num_planes;
	t_cylinder		**cylinders;
	int				num_cylinders;
}	t_setting;
