/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_select.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atucci <atucci@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 16:26:42 by atucci            #+#    #+#             */
/*   Updated: 2025/02/10 18:59:16 by atucci           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

/* this function do not work */
t_object *find_original_object(t_setting *setting, void *original_addr, t_type obj_type)
{
	int	i;

	i = 0;
	if (obj_type == T_SPHERE)
	{
		while (i < setting->num_spheres)
		{
			if ((void *)setting->spheres[i] == original_addr)
				return (t_object *)setting->spheres[i];
			i++;
		}
	}
	else if (obj_type == T_PLANE)
	{
		while (i < setting->num_planes)
		{
			if ((void *)setting->planes[i] == original_addr)
				return (t_object *)setting->planes[i];
			i++;
		}
	}
	else if (obj_type == T_CYLINDER)
	{
		while (i < setting->num_cylinders)
		{
			if ((void *)setting->cylinders[i] == original_addr)
				return (t_object *)setting->cylinders[i];
			i++;
		}
	}
	printf("Error: Original object not found!\nreturning NULL\n\n");
	return (NULL);
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
		//mlx->selected_object = &(hit->obj);
		find_original_object(setting, hit->obj.original_addr, hit->obj.type);
		printf("Selected object: %p\n", hit->obj.original_addr);
		/* Depending on the object type, cast and print its fields:
		if (hit->obj.type == T_SPHERE)
			printf("Sphere Selected:\n");
		else if (hit->obj.type == T_PLANE)
			printf("Plane Selected:\n");
		else if (hit->obj.type == T_CYLINDER)
			printf("Cylinder Selected:\n");
		else
			printf("not found\n");
		*/
		
	}
	else
		printf("Missed ray :(\n");
	free_list(&all_intersections);
	return (0);
}

