/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_single.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atucci <atucci@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 16:27:56 by atucci            #+#    #+#             */
/*   Updated: 2025/02/19 16:34:08 by atucci           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

void	print_vector(t_vector vector)
{
	printf("x: %f ", vector.x);
	printf("y: %f ", vector.y);
	printf("z: %f ", vector.z);
	printf("%sw:%s %f\n", BLUE, RESET, vector.w);
}

//3
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

//2
void	print_single_cylinder(t_cylinder *cyl)
{
	printf("colors : ");
	print_color(cyl->color);
	printf("Center of the cylinder: ");
	print_vector(cyl->center);
	printf("normalized vector of axis of cylinder : ");
	print_vector(cyl->axis);
	printf("diameter: %f & height: %f\n", cyl->diameter, cyl->height);
}

//1
void	print_single_plane(t_plane *one_plane)
{
	printf("colors : ");
	print_color(one_plane->color);
	printf("Point of the plane: ");
	print_vector(one_plane->point);
	printf("Normal vector of the plane: ");
	print_vector(one_plane->normal);
}
