/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   freeing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atucci <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 19:35:20 by atucci            #+#    #+#             */
/*   Updated: 2024/08/03 14:57:37 by atucci           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include <stdio.h>

/*
void	free_lights_array(t_light **lights, int num);
{
	int	counter;

	counter = 0;
	while (counter < num)
	{
		//free_single_light(lights[count]);
		count++;
	}
}

void	free_sphere_array(t_sphere **spheres, int num);
{
	int	counter;

	counter = 0;
	while (counter < num)
	{
		//free_single_sphere(spheres[count]);
		count++;
	}
}

void	free_plane_array(t_plane **planes, int num);
{
	int	counter;

	counter = 0;
	while (counter < num)
	{
		//free_single_plane(planes[count]);
		count++;
	}
}

void	free_cylinder_array(t_cylinder **cylinders, int num);
{
	int	counter;

	counter = 0;
	while (counter < num)
	{
		//free_single_cylinder(cylinders[count]);
		count++;
	}
}
*/

void	free_struct(t_setting *set)
{
	(void)set;
	printf("%sRemember to free all the memory%s\n", RED, RESET);
	free(set->amb_light->identifier);
	free(set->camera->identifier);
	//fee(set->light->identifier);
	free(set->amb_light);
	free(set->camera);
	//free(set->light);
}
// ok
