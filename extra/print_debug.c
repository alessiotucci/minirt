/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_debug.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atucci <atucci@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 11:45:15 by atucci            #+#    #+#             */
/*   Updated: 2025/02/19 17:19:04 by atucci           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"
#include <stdio.h>//TODO: printf is forbidden
//5
void	print_planes(int n_planes, t_plane **array)
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

//4
void	print_cylinders(int n_cylinders, t_cylinder **array)
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

//3
void	print_spheres(int n_spheres, t_sphere **array)
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

//2
void	print_single_light(t_light *one_light)
{
	printf("colors : ");
	print_color(one_light->color);
	printf("Position of the light: ");
	print_vector(one_light->position);
	printf("Brightness of the light: %f \n", one_light->brightness);
}

//1
void	print_lights(int n_lights, t_light **array)
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
