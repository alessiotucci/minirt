/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cast_ray.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atucci <atucci@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/27 13:23:43 by atucci            #+#    #+#             */
/*   Updated: 2024/09/27 14:59:15 by atucci           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

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
	return (ray);
}


t_vector project_point_to_2d(t_vector point, t_camera *camera, int width, int height)
{
	// Assuming camera is at the origin and looking along the z-axis
	double aspect_ratio = (double)width / (double)height;
	double fov_adjustment = tan(camera->fov * 0.5 * M_PI / 180.0);

	t_vector screen_point;
	screen_point.x = (point.x / (fov_adjustment * aspect_ratio)) / point.z;
	screen_point.y = (point.y / fov_adjustment) / point.z;

	// Convert to screen coordinates
	screen_point.x = (screen_point.x + 1) * 0.5 * width;
	screen_point.y = (1 - screen_point.y) * 0.5 * height; // Invert y for screen space

	// Clamp the coordinates to be within the screen bounds
	if ((screen_point.x < 0) || (screen_point.x >= width) || (screen_point.y < 0) || (screen_point.y >= height))
		printf("%sCLAMPING VALUE!%s\n", RED, RESET);
	if (screen_point.x < 0)
		screen_point.x = 1;
	if (screen_point.x >= width)
		screen_point.x = width - 2;
	if (screen_point.y < 0)
		screen_point.y = 1;
	if (screen_point.y >= height)
		screen_point.y = height - 2;

	return screen_point;
}

void	print_light_source(t_mlx *data, int x, int y)
{
	printf("finally print out the light point: x: %d, y: %d\n", x, y);
	my_mlx_pixel_put(data, x, y, COLOR_WHITE);
	my_mlx_pixel_put(data, x + 1, y, COLOR_WHITE);
	my_mlx_pixel_put(data, x, y + 1, COLOR_WHITE);
	my_mlx_pixel_put(data, x + 1, y + 1, COLOR_WHITE);
	my_mlx_pixel_put(data, x - 1, y - 1, COLOR_WHITE);
	my_mlx_pixel_put(data, x + 1, y - 1, COLOR_WHITE);
	my_mlx_pixel_put(data, x -1 , y + 1, COLOR_WHITE);
}

//TODO: LAST VERSION OF GPT
void	cast_rays(t_mlx *data)
{
	int					x;
	int					y;

//	t_ray				ray;
//
//	t_intersection_list	*all_intersections;
//	t_intersection		*closest_intersection;
//	t_intersection_list	*sphere_intersections;

	y = 0;
	while(y < data->height)
	{
		x = 0;
		while (x < data->width)
		{
			//each_pixel_calculation(data, x, y);
			each_pixel_calculationV2(data, x, y);
			/*ray = create_ray_from_camera(data, x, y);
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
				//printf("\n");
				t_vector point = position_ray(ray, closest_intersection->t);
				t_vector normal = v2normal_at(closest_intersection->obj, point);
				//printf("\t\there, after normal_at v2!\n");
				t_vector eye = negate(ray.direction);
				t_material m = material(); // Default material
				t_color color = lighting(m, *data->setting->lights[0], point, eye, normal);
				//print_color(color);
				my_mlx_pixel_put(data, x, y, create_trgb(color));
				//my_mlx_pixel_put(data, x, y, calculate_sphere_color(closest_intersection));
			}
			else
			{
				//printf("%sDEBUG%s closes intersection is null\n", BG_RED, BG_RESET);
				//printf(" | miss: [%d, %d] |\n", x, y);
				my_mlx_pixel_put(data, x, y, COLOR_BLACK);  // Background color
			}
			free(all_intersections->intersections);
			free(all_intersections);
			*/
		x++;
		}
	y++;
	}
	/*TODO print the lightpoint of white
	t_vector light_position = data->setting->lights[0]->position;
	t_vector screen_coords = project_point_to_2d(light_position, data->setting->camera, data->width, data->height);
	int light_x = (int)screen_coords.x;
	int light_y = (int)screen_coords.y;
	print_light_source(data, light_x, light_y);
	*/
}

//EACH PIXEL CALCUALTION ()
