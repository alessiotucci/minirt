/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cast_ray.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atucci <atucci@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/27 13:23:43 by atucci            #+#    #+#             */
/*   Updated: 2024/07/28 11:33:53 by atucci           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

// This function creates a ray from the camera's viewpoint towards a specific pixel on the screen.
// The ray is used in ray tracing to determine what object, if any, is seen by the camera at that pixel.
// The direction of the ray is a vector pointing from the camera's viewpoint towards the pixel on the screen.
// The x and y components of the vector are calculated by subtracting the coordinates of the pixel from the center of the screen.
// The z component of the vector is the same as the z component of the camera's direction.
// The resulting vector is then normalized to ensure its length is 1.

/*
t_ray	create_ray_from_camera(t_mlx *data, int x, int y)
{
	t_ray	ray;
	ray.origin = data->setting->camera->viewpoint;
	//printf("\n%sDEBUG HERE:%s manage_mlx.c/create_ray_from_camera\n", YELLOW, RESET);
	//printf("x: %d, y: %d, WIDTH: %d, HEIGHT: %d\n", x, y, data->width, data->height);
	ray.direction = normalization(create_vector(x - data->width / 2.0, data->height / 2.0 - y, data->setting->camera->orientation.z));
	//printf("\nray.direction x: %lf, y: %lf, z: %lf\n", x - width / 2.0, height / 2.0 - y, camera->orientation.z);
	//print_ray(ray);
	return (ray);
}

*/


//t_ray	create_ray_from_camera(t_camera *camera, int x, int y, int width, int height)
t_ray	create_ray_from_camera(t_mlx *data, int x, int y)
{
	t_ray		ray;
	t_vector	direction;
	double		screen_x;
	double		screen_y;
	double		ndc_x;
	double		ndc_y;

	//printf("x: %d, y: %d, WIDTH: %d, HEIGHT: %d\n", x, y, data->width, data->height);
	ray.origin = data->setting->camera->viewpoint;
	// Calculate normalized device coordinates
	ndc_x = (x + 0.5) / data->width;
	ndc_y = (y + 0.5) / data->height;
	// Convert NDC to screen space coordinates
	screen_x = (2 * ndc_x - 1) * data->setting->camera->image_plane_width / 2;
	screen_y = (1 - 2 * ndc_y) * data->setting->camera->image_plane_height / 2;
	// Calculate ray direction
	direction = create_vector(screen_x, screen_y, -1); // assuming camera looks down -Z axis
	ray.direction = normalization(direction);
	//print_ray(ray);
	return (ray);
}


//TODO: LAST VERSION OF GPT
void	cast_rays(t_mlx *data)
{
	int					x;
	int					y;
	int					i;
	t_ray				ray;
	t_intersection_list	*all_intersections;
	t_intersection		*closest_intersection;
	t_intersection_list	*sphere_intersections;

	y = 0;
	while(y < data->height)
	{
		x = 0;
		while (x < data->width)
		{
			ray = create_ray_from_camera(data, x, y);//(data->setting->camera, x, y, data->width, data->height);
			all_intersections = malloc(sizeof(t_intersection_list));
			all_intersections->count = 0;
			all_intersections->intersections = malloc(sizeof(t_intersection) * data->setting->num_spheres * 2);
			i = 0;
			while (i < data->setting->num_spheres)
			{
				printf("%sDEBUG%s sphere intersection[%d], please wait...\n", RED, RESET, i);
				sphere_intersections = intersect_sphere(*data->setting->spheres[i], ray);
				if (sphere_intersections)
					add_intersections_to_list(all_intersections, sphere_intersections);
			i++;
			}
			closest_intersection = hit(all_intersections);
			if (closest_intersection != NULL)
			{
				//printf("%sDEBUG%s closes intersection\n", BG_RED, BG_RESET);
				/*printf("\n");
				print_intersection(*closest_intersection);
				printf("\n");*/
				my_mlx_pixel_put(data, x, y, calculate_sphere_color(closest_intersection));
			}
			else
			{
				//printf("%sDEBUG%s closes intersection is null\n", BG_RED, BG_RESET);
				my_mlx_pixel_put(data, x, y, 0x000000);  // Background color
			}
			free(all_intersections->intersections);
			free(all_intersections);
		x++;
		}
	y++;
	}
}

