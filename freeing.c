/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   freeing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atucci <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 19:35:20 by atucci            #+#    #+#             */
/*   Updated: 2025/02/19 17:13:24 by atucci           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include <stdio.h>
#include <stdlib.h>

//1
void	free_single_sphere(t_sphere *sphere)
{
	if (sphere)
	{
		free(sphere->identifier);
		free_heap_matrix(sphere->transform, 4);
		free(sphere);
	}
}

//2
void	free_single_plane(t_plane *plane)
{
	if (plane)
	{
		free(plane->identifier);
		free_heap_matrix(plane->transform, 4);
		free(plane);
	}
}

//3
void	free_single_cylinder(t_cylinder *cylinder)
{
	if (cylinder)
	{
		free(cylinder->identifier);
		free_heap_matrix(cylinder->transform, 4);
		free(cylinder);
		return ;
	}
}

//4
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

//5
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
