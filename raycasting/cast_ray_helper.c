/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cast_ray_helper.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atucci <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 15:39:43 by atucci            #+#    #+#             */
/*   Updated: 2025/02/07 13:02:02 by atucci           ###   ########.fr       */
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
		sphere = (t_sphere *)obj.address; // casting
		return (sphere->color);
	}
	if (obj.type == T_PLANE)
	{
		//printf("ok: color of the plane is ");
		plane = (t_plane *)obj.address; // casting
		//print_single_plane(plane);
		//print_color(plane->color);
		return (plane->color);
	}
	if (obj.type == T_CYLINDER)
	{
		cylinder = (t_cylinder *)obj.address;
		//printf("GET_COLOR: %scylinder%s\n", BG_CYAN, BG_RESET);
		return (cylinder->color);
	}
	printf("Unexpected obj\n"); exit(-42);
	return (create_color(1, 1, 1));
}

void	each_pixel_calculationV2(t_mlx *data, int x, int y)
{
	t_ray	ray;
	t_list_intersect *all_intersections = NULL;
	t_intersection *closest_intersection;
	t_list_intersect *sphere_intersections;(void)sphere_intersections;
	t_list_intersect *cylinder_intersections;(void)cylinder_intersections;
	int	i;

	ray = create_ray_from_camera(data, x, y);
	i = 0;
	while (i < data->setting->num_spheres)
	{
		sphere_intersections = intersect_sphereV2(*data->setting->spheres[i], ray);
		if (sphere_intersections)
			concatenate_lists(&all_intersections, sphere_intersections);
	i++;
	}
	//Starting working here to see a plane on the screen
	t_list_intersect *plane_intersections;(void)plane_intersections;
	i = 0;
	while (i < data->setting->num_planes)
	{
		//printf("%sDEBUG%s plane intersection[%d], please wait...\n", RED, RESET, i);
		plane_intersections = intersect_plane(*data->setting->planes[i], ray);//TODO:
		if (plane_intersections)
			concatenate_lists(&all_intersections, plane_intersections);
	i++;
	}
	
	//Starting working here to try see a cylinder on the screen
	//t_list_intersect *cylinder_intersections;
	
	i = 0;
	while (i < data->setting->num_cylinders)
	{
		//printf("%sDEBUG%s cylinder intersection[%d], please wait...\n", RED, RESET, i);
		cylinder_intersections = intersect_cylinder(*data->setting->cylinders[i], ray);//TODO:
		if (cylinder_intersections)
			concatenate_lists(&all_intersections, cylinder_intersections);
		
	i++;
	}
	
	//TODO: here after checking for all the obj (sphere, cylinder, planes etc.) we check the closest point.
	//print_intersection_list(all_intersections);
	print_list(&all_intersections, 0);
	closest_intersection = hit_v2(all_intersections);
	if (closest_intersection != NULL)
	{
		/******************************************************************/
		/* variable are used to calculate the color, material m for phong */
		/******************************************************************/
		t_vector point = position_ray(ray, closest_intersection->t);
		t_vector normal = v2normal_at(closest_intersection->obj, point);
		t_vector eye = negate(ray.direction);
		t_material m = material();
		t_color phong_color = phong_lighting(m, *data->setting->lights[0], point, eye, normal);
		(void)phong_color;

	// Prepare computations for the hit.
		t_computations comps = prepare_computations(*closest_intersection, ray);
		t_color final_color = shade_hit(data->setting, comps, closest_intersection, eye);
		(void)final_color;

			my_mlx_pixel_put(data, x, y, create_trgb(final_color));
			//my_mlx_pixel_put(data, x, y, create_trgb(phong_color));
			//my_mlx_pixel_put(data, x, y, create_trgb(std));
		return ; //why here there is this return? TODO: check if the return
	}															 // leakss!!
	else
		my_mlx_pixel_put(data, x, y, COLOR_BLACK);
	free_list(&all_intersections);
}

