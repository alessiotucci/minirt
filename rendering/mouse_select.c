/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_select.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atucci <atucci@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 16:26:42 by atucci            #+#    #+#             */
/*   Updated: 2025/02/17 19:40:09 by atucci           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

#include <stdio.h>

// Searches an array of pointers for a target pointer and returns its index (or -1 if not found).
static int	search_index(void **array, int count, void *target)
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

// Helper: Search for sphere index.
static t_selected_obj	find_original_sphere(t_setting *setting, void *original_addr)
{
	t_selected_obj	sel;

	sel.index = search_index((void **)setting->spheres, setting->num_spheres, original_addr);
	if (sel.index != -1)
		sel.type = T_SPHERE;
	else
		sel.type = T_NULL;
	if (sel.index != -1)
		printf("Creating selected obj: index:%d, type: %s\n", sel.index, type_to_string(sel.type));
	return sel;
}

// Helper: Search for plane index.
static t_selected_obj	find_original_plane(t_setting *setting, void *original_addr)
{
	t_selected_obj	sel;

	sel.index = search_index((void **)setting->planes, setting->num_planes, original_addr);
	if (sel.index != -1)
		sel.type = T_PLANE;
	else
		sel.type = T_NULL;
	if (sel.index != -1)
		printf("Creating selected obj: index:%d, type: %s\n", sel.index, type_to_string(sel.type));
	return (sel);
}

// Helper: Search for cylinder index.
static t_selected_obj	find_original_cylinder(t_setting *setting, void *original_addr)
{
	t_selected_obj	sel;

	sel.index = search_index((void **)setting->cylinders, setting->num_cylinders, original_addr);
	if (sel.index != -1)
		sel.type = T_CYLINDER;
	else
		sel.type = T_NULL;
	if (sel.index != -1)
		printf("Creating selected obj: index:%d, type: %s\n", sel.index, type_to_string(sel.type));
	return (sel);
}

// Main function: select the correct helper based on object type.
t_selected_obj find_original_object_index(t_setting *setting, void *original_addr, t_type obj_type)
{
	t_selected_obj	sel;

	sel.index = -1;
	sel.type = T_NULL;
	if (obj_type == T_SPHERE)
		sel = find_original_sphere(setting, original_addr);
	else if (obj_type == T_PLANE)
		sel = find_original_plane(setting, original_addr);
	else if (obj_type == T_CYLINDER)
		sel = find_original_cylinder(setting, original_addr);
	else
		printf("Error: Invalid object type!\n");
	if (sel.index == -1)
		printf("Error: Original object not found!\n");
	return (sel);
}


int	cast_mouse_ray(int x, int y, t_mlx *mlx, t_setting *setting)
{
	printf("CAST_MOUSE_RAY!\n");
	t_ray	ray;
	t_list_intersect	*all_intersections;
	t_intersection	*hit;

	(void)all_intersections;
	(void)hit;
	(void)mlx;
	ray = create_ray_from_camera(mlx, x, y);
	all_intersections = intersect_world(setting, ray);
	hit = hit_v2(all_intersections);
	if (hit != NULL)
	{
		// Store the selected object in your world/setting.
		//mlx->selected = find_original_object(setting, hit->obj.original_addr, hit->obj.type);
		mlx->selected = find_original_object_index(setting, hit->obj.original_addr, hit->obj.type);
		printf("Selected object: %p\n", hit->obj.original_addr);
	}
	else
	{
		//mlx->selected_object = NULL;
		reset_selected_object(&mlx->selected);
		printf("Missed ray :(\n");
	}
	free_list(&all_intersections);
	return (0);
}

