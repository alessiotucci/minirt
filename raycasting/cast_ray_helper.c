/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cast_ray_helper.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftroise <ftroise@student.42roma.it>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 15:39:43 by atucci            #+#    #+#             */
/*   Updated: 2024/09/20 21:32:14 by ftroise          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

t_color	get_color_intersect(t_object obj)
{
	t_sphere	*sphere;

	if (obj.type == T_SPHERE)
	{
		sphere = (t_sphere *)obj.address; // casting
		return (sphere->color);
	}
	return (create_color(1, 1, 1));
}

/*original void	each_pixel_calculation(t_mlx *data, int x, int y)
{
	t_ray				ray;
	t_intersection_list	*all_intersections;
	t_intersection		*closest_intersection;
	t_intersection_list	*sphere_intersections;
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
	closest_intersection = hit(all_intersections);
	if (closest_intersection != NULL)
	{
		//printf("%sDEBUG%s VERBOSE LOG:\t⚠️ Inside the cast_ray function \n", BG_RED, BG_RESET);
		printf(" | hit! pixel values: [%s%d, %d%s] |\n", GREEN, x, y, RESET);
		//print_intersection(*closest_intersection);
		printf("printing the ray in question:\n");
		print_ray(ray);
		t_vector point = position_ray(ray, closest_intersection->t);
		t_vector normal = v2normal_at(closest_intersection->obj, point);
		//printf("\t\there, after normal_at v2!\n");
		//t_vector eye = negate(ray.direction);
		//t_material m = material(); // Default material
	//	t_color color = lighting(m, *data->setting->lights[0], point, eye, normal);
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
}*/

void each_pixel_calculation(t_mlx *data, int x, int y)
{
    t_ray ray;
    t_intersection_list *all_intersections;
    t_intersection *closest_intersection;
    t_intersection_list *sphere_intersections;
    int i;

    ray = create_ray_from_camera(data, x, y);
    all_intersections = malloc(sizeof(t_intersection_list));
    all_intersections->count = 0;
    all_intersections->intersections = malloc(sizeof(t_intersection) * data->setting->num_spheres * 2);

    i = 0;
    while (i < data->setting->num_spheres)
    {
        sphere_intersections = intersect_sphere(*data->setting->spheres[i], ray, data);
        if (sphere_intersections)
        {
            add_intersections_to_list(all_intersections, sphere_intersections);
            // Libera la memoria di sphere_intersections dopo aver aggiunto le sue intersezioni
            free(sphere_intersections->intersections);
            free(sphere_intersections);
        }
        i++;
    }

    closest_intersection = hit(all_intersections);
    if (closest_intersection != NULL)
    {
        t_vector point = position_ray(ray, closest_intersection->t);
        t_vector normal = v2normal_at(closest_intersection->obj, point);
        t_color std = get_color_intersect(closest_intersection->obj);
        t_color color = lambert_formula(std, *data->setting->lights[0], point, normal);
        my_mlx_pixel_put(data, x, y, create_trgb(color));
    }
    else
    {
        my_mlx_pixel_put(data, x, y, COLOR_BLACK);
    }

    free(all_intersections->intersections);
    free(all_intersections);
}
