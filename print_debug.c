/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_debug.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atucci <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 11:45:15 by atucci            #+#    #+#             */
/*   Updated: 2024/05/11 14:49:24 by atucci           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/* Helper function, I will delete this later on */
void struct_status(t_setting *set)
{
	ft_printf("\n\n------STRUCT STATUS -------\n");
	ft_printf("struct has [%d] planes \t  |\n", set->num_planes);
	ft_printf("struct has [%d] cylinders  |\n", set->num_cylinders);
	ft_printf("struct has [%d] spheres \t  |\n", set->num_spheres);
	ft_printf("struct has [%d] lights\t  |\n", set->num_lights);
	//ft_printf("struct has [%d] cones bonus|\n", set->num_cones);
	ft_printf("---------------------------\n\n");
}

void	print_color(t_color color)
{
	ft_printf("%sR: %d %s", RED, color.r, RESET);
	ft_printf("%sG: %d %s", GREEN, color.g, RESET);
	ft_printf("%sB: %d%s\n", BLUE, color.b, RESET);
}
void	print_vector(t_vector vector)
{
	ft_printf("x: %d ", vector.x);
	ft_printf("y: %d ", vector.y);
	ft_printf("z: %d\n",vector.z);
}

static void	print_single_plane(t_plane *one_plane)
{
		ft_printf("colors : ");
		print_color(one_plane->color);
		ft_printf("Point of the plane: ");
		print_vector(one_plane->point);
		ft_printf("Normal vector of the plane: ");
		print_vector(one_plane->normal);

}
static void	print_planes(int n_planes, t_plane **array)
{
	int	i;

	i = 0;
	while (i < n_planes)
	{
		ft_printf("Planes[%d]", i);
		print_single_plane(array[i]);
		i++;
	}
}

static void	print_single_cylinder(t_cylinder *one_cylinder)
{
		ft_printf("colors : ");
		print_color(one_cylinder->color);
		ft_printf("Center of the cylinder: ");
		print_vector(one_cylinder->center);
		ft_printf("normalized vector of axis of cylinder : ");
		print_vector(one_cylinder->axis);
		ft_printf("diameter: %f & height: %f\n", one_cylinder->diameter, one_cylinder->height);

}
static void	print_cylinders(int n_cylinders, t_cylinder **array)
{
	int	i;

	i = 0;
	while (i < n_cylinders)
	{
		ft_printf("Cylinders[%d]", i);
		print_single_cylinder(array[i]);
		i++;
	}
}

static void	print_single_sphere(t_sphere *one_sphere)
{
		ft_printf("colors : ");
		print_color(one_sphere->color);
		ft_printf("Center of the Sphere: ");
		print_vector(one_sphere->center);
		ft_printf("Diameter: %f\n", one_sphere->diameter);

}
static void	print_spheres(int n_spheres, t_sphere **array)
{
	int	i;

	i = 0;
	while (i < n_spheres)
	{
		ft_printf("Spheres[%d]", i);
		print_single_sphere(array[i]);
		i++;
	}
}

static void	print_single_light(t_light *one_light)
{
		ft_printf("colors : ");
		print_color(one_light->color);
		ft_printf("Position of the light: ");
		print_vector(one_light->position);
		ft_printf("Brightness of the light: %f \n", one_light->brightness);

}
static void	print_lights(int n_lights, t_light **array)
{
	int	i;

	i = 0;
	while (i < n_lights)
	{
		ft_printf("Lights[%d]", i);
		print_single_light(array[i]);
		i++;
	}
}

void	struct_full_status(t_setting *set)
{
	ft_printf("\n\n------STRUCT %sFULL %sSTATUS -------\n", PURPLE, RESET);
	ft_printf("\n* n.[%s%d%s] PLANES \t\n", RED, set->num_planes, RESET);
	print_planes(set->num_planes, set->planes);
	ft_printf("\n* n.[%s%d%s] CYLINDERS  |\n", RED, set->num_cylinders, RESET);
	print_cylinders(set->num_cylinders, set->cylinders);
	ft_printf("\n* n.[%s%d%s] SPHERES \t  |\n", RED, set->num_spheres, RESET);
	print_spheres(set->num_spheres, set->spheres);
	ft_printf("\n* n.[%s%d%s] LIGHTS\t  |\n", RED, set->num_lights, RESET);
	print_lights(set->num_lights, set->lights);
	//ft_printf("struct has [%d] cones bonus|\n", set->num_cones);
	ft_printf("---------------------------\n\n");
}
