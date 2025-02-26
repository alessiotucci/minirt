/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   freeing2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atucci <atucci@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 17:07:24 by atucci            #+#    #+#             */
/*   Updated: 2025/02/26 10:18:20 by atucci           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minirt.h"

//3
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

//2
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

//1
void	free_struct(t_setting *set)
{
	printf("\n\n%sRemember to free all the memory%s\n", RED, RESET);
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
	printf("\n%sUpdated: working on validate the parser%s\n", YELLOW, RESET);
}
