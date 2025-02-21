/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_select.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atucci <atucci@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 16:26:42 by atucci            #+#    #+#             */
/*   Updated: 2025/02/19 17:56:16 by atucci           ###   ########.fr       */
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

/* 6! move to another file */
int	cast_mouse_ray(int x, int y, t_mlx *mlx, t_setting *set)
{
	t_ray				ray;
	t_list_intersect	*all_intersections;
	t_intersection		*ht;

	printf("CAST_MOUSE_RAY!\n");
	ray = create_ray_from_camera2(mlx, x, y);
	all_intersections = intersect_world(set, ray);
	ht = hit_v2(all_intersections);
	if (ht != NULL)
	{
		mlx->selected = find_original(set, ht->obj.original_addr, ht->obj.type);
		printf("Selected object: %p\n", ht->obj.original_addr);
	}
	else
	{
		reset_selected_object(&mlx->selected);
		printf("Missed ray :(\n");
	}
	free_list(&all_intersections);
	return (0);
}
