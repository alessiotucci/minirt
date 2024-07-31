/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_debug.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atucci <atucci@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 11:45:15 by atucci            #+#    #+#             */
/*   Updated: 2024/07/31 15:06:13 by atucci           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"
#include <stdio.h>//TODO: printf is forbidden
/* Helper function, I will delete this later on */
void	struct_status(t_setting *set)
{
	printf("\n\n------STRUCT STATUS -------\n");
	printf("struct has [%d] planes \t  |\n", set->num_planes);
	printf("struct has [%d] cylinders  |\n", set->num_cylinders);
	printf("struct has [%d] spheres \t  |\n", set->num_spheres);
	printf("struct has [%d] lights\t  |\n", set->num_lights);
	//printf("struct has [%d] cones bonus|\n", set->num_cones);
	printf("---------------------------\n\n");
}

void	print_color(t_color color)
{
	printf("\n%sR: %lf %s", RED, color.r, RESET);
	printf("%sG: %lf %s", GREEN, color.g, RESET);
	printf("%sB: %lf%s\n\n", BLUE, color.b, RESET);
}

void	print_vector(t_vector vector)
{
	printf("\nx: %f ", vector.x);
	printf("y: %f ", vector.y);
	printf("z: %f ",vector.z);
	printf("%sw:%s %f\n\n", BLUE, RESET, vector.w);
}

void	print_single_plane(t_plane *one_plane)
{
		printf("colors : ");
		print_color(one_plane->color);
		printf("Point of the plane: ");
		print_vector(one_plane->point);
		printf("Normal vector of the plane: ");
		print_vector(one_plane->normal);

}
static void	print_planes(int n_planes, t_plane **array)
{
	int	i;

	i = 0;
	while (i < n_planes)
	{
		printf("Planes[%d]", i);
		print_single_plane(array[i]);
		i++;
	}
}

void	print_single_cylinder(t_cylinder *one_cylinder)
{
		printf("colors : ");
		print_color(one_cylinder->color);
		printf("Center of the cylinder: ");
		print_vector(one_cylinder->center);
		printf("normalized vector of axis of cylinder : ");
		print_vector(one_cylinder->axis);
		printf("diameter: %f & height: %f\n", one_cylinder->diameter, one_cylinder->height);

}
static void	print_cylinders(int n_cylinders, t_cylinder **array)
{
	int	i;

	i = 0;
	while (i < n_cylinders)
	{
		printf("Cylinders[%d]", i);
		print_single_cylinder(array[i]);
		i++;
	}
}

void	print_single_sphere(t_sphere *one_sphere)
{
	printf("Address: %p\n", one_sphere);
	printf("colors : ");
	print_color(one_sphere->color);
	printf("material : ");
	print_material(one_sphere->material);
	printf("Center of the Sphere: ");
	print_vector(one_sphere->center);
	printf("Diameter: %f\n", one_sphere->diameter);
	printf("\tSphere Matrix:\t%p\n", one_sphere->transform);
	print_int_matrix(4, 4, one_sphere->transform);
}

static void	print_spheres(int n_spheres, t_sphere **array)
{
	int	i;

	i = 0;
	while (i < n_spheres)
	{
		printf("Spheres[%d]", i);
		print_single_sphere(array[i]);
		i++;
	}
}

void	print_single_light(t_light *one_light)
{
		printf("colors : ");
		print_color(one_light->color);
		printf("Position of the light: ");
		print_vector(one_light->position);
		printf("Brightness of the light: %f \n", one_light->brightness);

}
static void	print_lights(int n_lights, t_light **array)
{
	int	i;

	i = 0;
	while (i < n_lights)
	{
		printf("Lights[%d]", i);
		print_single_light(array[i]);
		i++;
	}
}

static void	print_camera(t_camera *camera)
{
	printf("ViewPoint: ");
	print_vector(camera->viewpoint);
	printf("Orentation: ");
	print_vector(camera->orientation);
	printf("FOV:[%d]\n", camera->fov);
}
static void	print_ambient_light(t_amb_light *amb_light)
{
	printf("Ratio of ambient lights: %f\n", amb_light->ratio);
	printf("Color of ambient lights: ");
	print_color(amb_light->color);

}
void	struct_full_status(t_setting *set)
{
	printf("\n\n------STRUCT %sFULL %sSTATUS -------\n", PURPLE, RESET);
	printf("\n*\t %sAMBIENT LIGHTS%s *\n", BLUE, RESET);
	print_ambient_light(set->amb_light);
	printf("\n*\t%sCAMERA STATS%s *\n", BLUE, RESET);
	print_camera(set->camera);
	printf("\n* n.[%s%d%s] PLANES \t\n", RED, set->num_planes, RESET);
	print_planes(set->num_planes, set->planes);
	printf("\n* n.[%s%d%s] CYLINDERS  |\n", RED, set->num_cylinders, RESET);
	print_cylinders(set->num_cylinders, set->cylinders);
	printf("\n* n.[%s%d%s] SPHERES \t  |\n", RED, set->num_spheres, RESET);
	print_spheres(set->num_spheres, set->spheres);
	printf("\n* n.[%s%d%s] LIGHTS\t  |\n", RED, set->num_lights, RESET);
	print_lights(set->num_lights, set->lights);
	//printf("struct has [%d] cones bonus|\n", set->num_cones);
	printf("---------------------------\n\n");
}
