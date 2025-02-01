/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cast_ray_helper.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atucci <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 15:39:43 by atucci            #+#    #+#             */
/*   Updated: 2025/02/01 18:35:41 by atucci           ###   ########.fr       */
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

/*
void	each_pixel_calculation(t_mlx *data, int x, int y)
{
	t_ray				ray;
	t_intersection_list	*all_intersections;
	t_intersection		*closest_intersection;
	t_intersection_list	*sphere_intersections;
	t_intersection_list	*plane_intersections;
	int					i;

	ray = create_ray_from_camera(data, x, y);
	all_intersections = malloc(sizeof(t_intersection_list));
	all_intersections->count = 0;
	all_intersections->intersections = malloc(sizeof(t_intersection) * data->setting->num_spheres * 2);
	i = 0;
	while (i < data->setting->num_spheres)
	{
		//printf("%sDEBUG%s sphere intersection[%d], please wait...\n", RED, RESET, i);
		sphere_intersections = intersect_sphere(*data->setting->spheres[i], ray);
		if (sphere_intersections)
			add_intersections_to_list(all_intersections, sphere_intersections);
	i++;
	}

	i = 0;
	while (i < data->setting->num_planes)
	{
		//printf("%sDEBUG%s sphere intersection[%d], please wait...\n", RED, RESET, i);
		plane_intersections = intersect_plane(*data->setting->planes[i], ray);//TODO:
		if (plane_intersections)
			add_intersections_to_list(all_intersections, plane_intersections);
	i++;
	}
	
	closest_intersection = hit(all_intersections);
	if (closest_intersection != NULL)
	{
		//printf("%sDEBUG%s VERBOSE LOG:\t⚠️ Inside the cast_ray function \n", BG_RED, BG_RESET);
		//printf(" | hit! pixel values: [%s%d, %d%s] |\n", GREEN, x, y, RESET);
		//print_intersection(*closest_intersection);
		//printf("printing the ray in question:\n");
		print_ray(ray);
		t_vector point = position_ray(ray, closest_intersection->t);
		t_vector normal = v2normal_at(closest_intersection->obj, point);
		//printf("\t\there, after normal_at v2!\n");
		//t_vector eye = negate(ray.direction);
		//t_material m = material(); // Default material
		//t_color color = lighting(m, *data->setting->lights[0], point, eye, normal);
		t_color std = get_color_intersect(closest_intersection->obj);
		t_color color = lambert_formula(std, *data->setting->lights[0], point, normal);
		//print_color(color);
		my_mlx_pixel_put(data, x, y, create_trgb(color));
		//my_mlx_pixel_put(data, x, y, calculate_sphere_color(closest_intersection));
	}
	else
		my_mlx_pixel_put(data, x, y, COLOR_BLACK);  // Background color
	free(all_intersections->intersections);
	free(all_intersections);
}
*/

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
	closest_intersection = hit_v2(all_intersections);
	if (closest_intersection != NULL)
	{
		//printf(" | hit! pixel values: [%s%d, %d%s] |\n", GREEN, x, y, RESET);
		//print_ray(ray);
		t_vector point = position_ray(ray, closest_intersection->t);
		t_vector normal = v2normal_at(closest_intersection->obj, point);
	//	t_vector eye = negate(ray.direction);
	//	t_material m = material(); // Default material
		//t_color color = phong_lighting(m, *data->setting->lights[0], point, eye, normal);

		/*t_color std = get_color_intersect(closest_intersection->obj);*/
		t_color color = lambert_formula(closest_intersection, *data->setting->lights[0], point, normal, data->setting); //TODO: this is not normed, check data
		(void)color;
		/*
		if (closest_intersection->obj.type == T_SPHERE)
			printf("DEBUG: from the SPHERE (%d, %d)\n", x, y);
		if (closest_intersection->obj.type == T_CYLINDER)
			printf("\nDEBUG: from the CILINDRO (%d, %d)\n", x, y);
		*/
		//print_color(std);
//		if (closest_intersection->obj.type != T_PLANE)
			//printf("x:%d, y:%d\n", x, y);
			//my_mlx_pixel_put(data, x, y, COLOR_YELLOW);  // I suck at coding
			my_mlx_pixel_put(data, x, y, create_trgb(color));
//		else
//			my_mlx_pixel_put(data, x, y, create_trgb(std));
		return ;
	}
	else
	{
		//printf("x:%d, y:%d\n", x, y);
		my_mlx_pixel_put(data, x, y, COLOR_BLACK);  // Background color
	}
	free_list(&all_intersections);
}

