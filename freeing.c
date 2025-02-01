/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   freeing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atucci <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 19:35:20 by atucci            #+#    #+#             */
/*   Updated: 2025/02/01 18:34:35 by atucci           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include <stdio.h>
#include <stdlib.h>

void	free_single_sphere(t_sphere *sphere)
{
	if (sphere)
	{
		free(sphere->identifier);
		free_heap_matrix(sphere->transform, 4); // Assuming free_matrix correctly frees a 2D array
		free(sphere);
	}
}

void	free_single_plane(t_plane *plane)
{
	if (plane)
	{
		free(plane->identifier);
		free_heap_matrix(plane->transform, 4); // Assuming free_matrix correctly frees a 2D array
		free(plane);
	}
}

void	free_single_cylinder(t_cylinder *cylinder)
{
	//printf("%sSEGFAULT%s\nfree_single_cylinder: freeing.c\n", RED, RESET);
	if (cylinder)
	{
		free(cylinder->identifier);
		free_heap_matrix(cylinder->transform, 4); // Assuming free_matrix correctly frees a 2D array
		free(cylinder);
		return ;
	}
}


void	free_lights_array(t_light **lights, int num)
{
	int	count;

	count = 0;
	while (count < num)
	{
		free(lights[count]->identifier);
		free(lights[count]);
		count++;
	}
	free(lights);
}

void	free_sphere_array(t_sphere **spheres, int num)
{
	int	count;

	count = 0;
	while (count < num)
	{
		free_single_sphere(spheres[count]);
		count++;
	}
	free(spheres);
}

void	free_plane_array(t_plane **planes, int num)
{
	int	count;

	count = 0;
	while (count < num)
	{
		free_single_plane(planes[count]);
		count++;
	}
	free(planes);
}

void	free_cylinder_array(t_cylinder **cylinders, int num)
{
	int	count;

	count = 0;
	while (count < num)
	{
		free_single_cylinder(cylinders[count]);
		count++;
	}
	free(cylinders);
}


void	free_struct(t_setting *set)
{
	printf("%sRemember to free all the memory%s\n", RED, RESET);
	printf("%sUPDATE 1 Feb: fixing cylinder%s\n", RED, RESET);
	if (set->amb_light)
	{
		free(set->amb_light->identifier);
		free(set->amb_light);
	}
	if (set->camera)
	{
		free(set->camera->identifier);
		free(set->camera);
	}
	free_sphere_array(set->spheres, set->num_spheres);
	free_lights_array(set->lights, set->num_lights);
	free_plane_array(set->planes, set->num_planes);
	free_cylinder_array(set->cylinders, set->num_cylinders);
}
