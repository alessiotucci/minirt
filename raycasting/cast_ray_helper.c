/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cast_ray_helper.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atucci <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 15:39:43 by atucci            #+#    #+#             */
/*   Updated: 2025/02/23 18:08:41 by atucci           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

t_color	get_color_intersect(t_object obj)
{
	t_sphere	*sphere;
	t_plane		*plane;
	t_cylinder	*cylinder;

	if (obj.type == T_SPHERE)
	{
		sphere = (t_sphere *)obj.address;
		return (sphere->color);
	}
	if (obj.type == T_PLANE)
	{
		plane = (t_plane *)obj.address;
		return (plane->color);
	}
	if (obj.type == T_CYLINDER)
	{
		cylinder = (t_cylinder *)obj.address;
		return (cylinder->color);
	}
	printf("Unexpected obj: creating standard color!!!\n");
	return (create_color(1, 1, 1));
}

void	each_pixel_calculation(t_mlx *data, int x, int y)
{
	t_ray				ray;
	t_list_intersect	*all_intersections;
	t_intersection		*closest_intersection;
	t_computations		comps;
	t_color				final_color;

	all_intersections = NULL;
	ray = create_ray_from_camera2(data, x, y);
	all_intersections = intersect_world(data->setting, ray);
	closest_intersection = hit_v2(all_intersections);
	if (closest_intersection != NULL)
	{
		comps = prepare_computations(*closest_intersection, ray);
		final_color = shade_hit(data->setting, comps);
		my_mlx_pixel_put(data, x, y, create_trgb(final_color));
	}
	else
		my_mlx_pixel_put(data, x, y, COLOR_BLACK);
	free_list(&all_intersections);
}
