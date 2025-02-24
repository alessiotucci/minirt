/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_select.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atucci <atucci@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 16:26:42 by atucci            #+#    #+#             */
/*   Updated: 2025/02/24 16:57:23 by atucci           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

#include <stdio.h>

// Searches an array of pointers for a target pointer
// and returns its index (or -1 if not found).
// 1
static int	search_i(void **array, int count, void *target)
{
	int	i;

	i = 0;
	while (i < count)
	{
		if (array[i] == target)
		{
			printf("%sFOUND!%s", GREEN, RESET);
			printf(" index: [%d]\n", i);
			return (i);
		}
		i++;
	}
	return (-1);
}

//2
// Helper: Search for sphere index.
static t_selected_obj	find_original_sphere(t_setting *setting, void *orig)
{
	t_selected_obj	s;

	s.index = search_i((void **)setting->spheres, setting->num_spheres, orig);
	if (s.index != -1)
		s.type = T_SPHERE;
	else
		s.type = T_NULL;
	return (s);
}

//3
// Helper: Search for plane index.
static t_selected_obj	find_original_plane(t_setting *setting, void *orig)
{
	t_selected_obj	s;

	s.index = search_i((void **)setting->planes, setting->num_planes, orig);
	if (s.index != -1)
		s.type = T_PLANE;
	else
		s.type = T_NULL;
	return (s);
}

//4
// Helper: Search for cylinder index.
static t_selected_obj	find_original_cylinder(t_setting *setting, void *o)
{
	t_selected_obj	s;

	s.index = search_i((void **)setting->cylinders, setting->num_cylinders, o);
	if (s.index != -1)
		s.type = T_CYLINDER;
	else
		s.type = T_NULL;
	return (s);
}

//5
// Main function: select the correct helper based on object type.
t_selected_obj	find_original(t_setting *setting, void *orig, t_type obj_type)
{
	t_selected_obj	s;

	s.index = -1;
	s.type = T_NULL;
	if (obj_type == T_SPHERE)
		s = find_original_sphere(setting, orig);
	else if (obj_type == T_PLANE)
		s = find_original_plane(setting, orig);
	else if (obj_type == T_CYLINDER)
		s = find_original_cylinder(setting, orig);
	else
		printf("Error: Invalid object type!\n");
	if (s.index == -1)
		printf("Error: Original object not found!\n");
	return (s);
}
