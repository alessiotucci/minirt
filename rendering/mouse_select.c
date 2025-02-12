/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_select.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atucci <atucci@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 16:26:42 by atucci            #+#    #+#             */
/*   Updated: 2025/02/12 17:21:13 by atucci           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

#include <stdio.h>

void	reset_selected_object(t_selected_obj selected)
{
	selected.index = -1;
	selected.type = T_NULL;
}

//TODO: refactor this function later on
t_selected_obj find_original_object_index(t_setting *setting, void *original_addr, t_type obj_type)
{
    t_selected_obj sel;
//	reset_selected_object(sel);
	sel.index = -1;
	sel.type = T_NULL;

    int i = 0;
    if (obj_type == T_SPHERE)
    {
        while (i < setting->num_spheres)
        {
            if (setting->spheres[i] == (t_sphere *)original_addr)
            {
                sel.index = i;
                sel.type = T_SPHERE;
            	printf("Creating selected obj: index:%d, type: %s\n", i, type_to_string(sel.type));
                return sel;
            }
            i++;
        }
    }
    else if (obj_type == T_PLANE)
    {
        while (i < setting->num_planes)
        {
            if (setting->planes[i] == (t_plane *)original_addr)
            {
                sel.index = i;
                sel.type = T_PLANE;
            	printf("Creating selected obj: index:%d, type: %s\n", i, type_to_string(sel.type));
                return sel;
            }
            i++;
        }
    }
    else if (obj_type == T_CYLINDER)
    {
        while (i < setting->num_cylinders)
        {
            if (setting->cylinders[i] == (t_cylinder *)original_addr)
            {
                sel.index = i;
                sel.type = T_CYLINDER;
            	printf("Creating selected obj: index:%d, type: %s\n", i, type_to_string(sel.type));
                return sel;
            }
            i++;
        }
    }
    printf("Error: Original object not found!\n");
    return sel;
}


// Assuming GREEN and RESET are defined elsewhere

/* returning an index and enum instead of a fucking t_obj pointer! */
static t_object	*search_array(void **array, int count, void *target)
{
	int	i;

	i = 0;
	while (i < count)
	{
		if (array[i] == target)
		{
			printf("%sFOUND!%s\n", GREEN, RESET);
			printf("index: [%d], type: wait ...\n", i);
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
		found = search_array((void **)setting->spheres, setting->num_spheres, original_addr);
	else if (obj_type == T_PLANE)
		found = search_array((void **)setting->planes, setting->num_planes, original_addr);
	else if (obj_type == T_CYLINDER)
		found = search_array((void **)setting->cylinders, setting->num_cylinders, original_addr);
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
		//mlx->selected = find_original_object(setting, hit->obj.original_addr, hit->obj.type);
		mlx->selected = find_original_object_index(setting, hit->obj.original_addr, hit->obj.type);
		printf("Selected object: %p\n", hit->obj.original_addr);
	}
	else
	{
		//mlx->selected_object = NULL;
		reset_selected_object(mlx->selected);
		printf("Missed ray :(\n");
	}
	free_list(&all_intersections);
	return (0);
}

