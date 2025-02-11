/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_select.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atucci <atucci@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 16:26:42 by atucci            #+#    #+#             */
/*   Updated: 2025/02/11 18:49:35 by atucci           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

#include <stdio.h>

// Assuming GREEN and RESET are defined elsewhere

/* returning an index and enum instead of a fucking t_obj pointer! */
static t_object	*search_array(void **array, int count, void *target, const char *type_name)
{
	int	i;

	i = 0;
	while (i < count)
	{
		if (array[i] == target)
		{
			printf("%sFOUND!%s %s, with index[%d]\n", GREEN, RESET, type_name, i);
			return ((t_object *)array[i]);
		}
		i++;
	}
	return (NULL);
}

t_object	*find_original_object(t_setting *setting, void *original_addr, t_type obj_type)
{
	t_object	*found;

	found = NULL;
	if (obj_type == T_SPHERE)
		found = search_array((void **)setting->spheres, setting->num_spheres, original_addr, "sphere");
	else if (obj_type == T_PLANE)
		found = search_array((void **)setting->planes, setting->num_planes, original_addr, "plane");
	else if (obj_type == T_CYLINDER)
		found = search_array((void **)setting->cylinders, setting->num_cylinders, original_addr, "cylinder");
	else
		printf("Error: Invalid object type!\n");
	if (!found)
		printf("Error: Original object not found!\nreturning NULL\n\n");
	return (found);
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
		mlx->selected_object = find_original_object(setting, hit->obj.original_addr, hit->obj.type);
		printf("Selected object: %p\n", hit->obj.original_addr);
	}
	else
	{
		mlx->selected_object = NULL;
		printf("Missed ray :(\n");
	}
	free_list(&all_intersections);
	return (0);
}

