/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cast_ray.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atucci <atucci@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/27 13:23:43 by atucci            #+#    #+#             */
/*   Updated: 2024/07/27 13:31:32 by atucci           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

// This function creates a ray from the camera's viewpoint towards a specific pixel on the screen.
// The ray is used in ray tracing to determine what object, if any, is seen by the camera at that pixel.
// The direction of the ray is a vector pointing from the camera's viewpoint towards the pixel on the screen.
// The x and y components of the vector are calculated by subtracting the coordinates of the pixel from the center of the screen.
// The z component of the vector is the same as the z component of the camera's direction.
// The resulting vector is then normalized to ensure its length is 1.
t_ray	create_ray_from_camera(t_camera *camera, int x, int y, int width, int height)
{
	t_ray	ray;
	ray.origin = camera->viewpoint;
	//printf("\n%sDEBUG HERE:%s manage_mlx.c/create_ray_from_camera\n", YELLOW, RESET);
	ray.direction = normalization(create_vector(x - width / 2.0, height / 2.0 - y, camera->orientation.z));
	return (ray);
}
/*
t_ray	create_ray_from_camera(t_camera *camera, int x, int y, int width, int height)
{
	t_ray ray;
	t_vector pixel_position;

	ray.origin = camera->viewpoint;

	// Compute the pixel position in camera space
	double aspect_ratio = (double)width / (double)height;
	double fov_adjustment = tan((camera->fov / 2.0) * (M_PI / 180.0));

	// Pixel coordinates normalized to [-1, 1]
	double pixel_ndc_x = (x + 0.5) / (double)width;
	double pixel_ndc_y = (y + 0.5) / (double)height;

	// Transform to screen space [-1, 1]
	double pixel_screen_x = 2 * pixel_ndc_x - 1;
	double pixel_screen_y = 1 - 2 * pixel_ndc_y;

	// Transform to camera space
	pixel_position.x = pixel_screen_x * aspect_ratio * fov_adjustment;
	pixel_position.y = pixel_screen_y * fov_adjustment;
	pixel_position.z = -1;  // Assuming the camera is pointing towards -z
	pixel_position.w = 0.0;

	printf("Ray Direction Before Normalization: x: %f y: %f z: %f w: %f\n", pixel_position.x, pixel_position.y, pixel_position.z, pixel_position.w);

	ray.direction = normalization(pixel_position);

	printf("Ray Direction After Normalization: x: %f y: %f z: %f w: %f\n", ray.direction.x, ray.direction.y, ray.direction.z, ray.direction.w);

	return ray;
}
*/

//TODO: LAST VERSION OF GPT
//
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
			ray = create_ray_from_camera(data->setting->camera, x, y, data->width, data->height);
			all_intersections = malloc(sizeof(t_intersection_list));
			all_intersections->count = 0;
			all_intersections->intersections = malloc(sizeof(t_intersection) * data->setting->num_spheres * 2);
			i = 0;
			while (i < data->setting->num_spheres)
			{
				sphere_intersections = intersect_sphere(*data->setting->spheres[i], ray);
				if (sphere_intersections)
					add_intersections_to_list(all_intersections, sphere_intersections);
			i++;
			}
			closest_intersection = hit(all_intersections);
			if (closest_intersection != NULL)
				my_mlx_pixel_put(data, x, y, calculate_sphere_color(closest_intersection));
			else
				my_mlx_pixel_put(data, x, y, 0x000000);  // Background color
			free(all_intersections->intersections);
			free(all_intersections);
		x++;
		}
	y++;
	}
}
/*
void cast_rays(t_mlx *data)
{
	int		x;
	int		y;
	t_ray	ray;
	t_intersection_list *all_intersections;
	t_intersection *closest_intersection;

	for (y = 0; y < data->height; y++)
	{
		for (x = 0; x < data->width; x++)
		{
			ray = create_ray_from_camera(data->setting->camera, x, y, data->width, data->height);
			all_intersections = create_intersection_list(0);  // Initialize an empty list
			// Find intersections with all spheres and add to the list
			for (int i = 0; i < data->setting->num_spheres; i++)
			{
				t_intersection_list *sphere_intersections = intersect_sphere(*data->setting->spheres[i], ray);
				add_intersections_to_list(all_intersections, sphere_intersections);
			}
			// Find the closest intersection using the hit function
			closest_intersection = hit(all_intersections);
			if (closest_intersection != NULL) //TODO let's see
				my_mlx_pixel_put(data, x, y, calculate_sphere_color(closest_intersection));
			else
				my_mlx_pixel_put(data, x, y, 0x000000);  // Background color
			
		}
	}
}
*/
