/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_scene.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atucci <atucci@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/27 13:24:15 by atucci            #+#    #+#             */
/*   Updated: 2024/08/01 15:36:19 by atucci           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include <time.h>

// FOV Calculation: The FOV will determine the size of the image plane.
// Use the horizontal FOV of 70 degrees.
// Convert FOV from degrees to radians
// Calculate the width of the image plane
void	fov_calculation(t_camera *cam, double *image_plane_width)
{
	double	fov_rad;

	fov_rad = cam->fov * (M_PI / 180.0);
	*image_plane_width = 2.0 * tan(fov_rad / 2.0);
}

//Aspect Ratio: Calculate the aspect ratio of your canvas (width/height).
void	aspect_ratio(t_mlx *mlx, double *aspect_ratio)
{
	*aspect_ratio = (double)mlx->width / (double)mlx->height;
}

//Image Plane Dimensions: Based on the FOV and aspect ratio,
//determine the width and height of the image plane.
void	image_plane_dimensions(t_mlx *mlx, double *width, double *height)
{
	double	aspect_ratio_value;

	fov_calculation(mlx->setting->camera, width);
	aspect_ratio(mlx, &aspect_ratio_value);
	*height = *width / aspect_ratio_value;
}

//Step 1: Define the Camera's Image Plane
void	camera_image_plane(t_mlx *mlx)
{
	double	width;
	double	height;

	image_plane_dimensions(mlx, &width, &height);
	printf("Image Plane Width: %f\n", width);
	printf("Image Plane Height: %f\n", height);
	mlx->setting->camera->image_plane_width = width;
	mlx->setting->camera->image_plane_height = height;
}

//TODO: this was the entry point
/* There is no need to center the sphere here ... */
void	draw_scene(t_mlx *data)
{
	clock_t	start_time;
	clock_t	end_time;

	camera_image_plane(data);
	start_time = clock();
	cast_rays(data);
	end_time = clock();
	printf("\n\tThe while loop took %s%.2f seconds%s to execute.\n", YELLOW, \
		(((double)end_time - start_time) / CLOCKS_PER_SEC), RESET);
}
