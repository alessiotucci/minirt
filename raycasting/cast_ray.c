/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cast_ray.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atucci <atucci@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/27 13:23:43 by atucci            #+#    #+#             */
/*   Updated: 2025/02/08 17:52:14 by atucci           ###   ########.fr       */
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
	//printf("DEBUG: Create ray from the camera with x[%d] and y[%d]\n next we will print the ray:\t", x, y);
	//print_ray(ray);
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

	y = 0;
	while(y < data->height)
	{
		x = 0;
		while (x < data->width)
		{
			each_pixel_calculationV2(data, x, y);
			
		x++;
		}
	y++;
	}
}
//EACH PIXEL CALCUALTION ():
