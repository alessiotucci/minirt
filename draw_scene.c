/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_scene.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atucci <atucci@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/27 13:24:15 by atucci            #+#    #+#             */
/*   Updated: 2024/07/27 15:36:44 by atucci           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include <time.h>

//FOV Calculation: The FOV will determine the size of the image plane. Use the horizontal FOV of 70 degrees.
void	fov_calculation(t_camera *cam, double *image_plane_width)
{
	double	fov_rad;
	double	distance;

	fov_rad = cam->fov * (M_PI / 180.0); // Convert FOV from degrees to radians
	distance = 1.0;// Assuming the distance from the camera to the image plane is 1 unit
	*image_plane_width = 2.0 * distance * tan(fov_rad / 2.0);// Calculate the width of the image plane
}

//Aspect Ratio: Calculate the aspect ratio of your canvas (width/height).
void	aspect_ratio(t_mlx *mlx, double *aspect_ratio)
{
	*aspect_ratio = (double)mlx->width / (double)mlx->height;
}


//Image Plane Dimensions: Based on the FOV and aspect ratio, determine the width and height of the image plane.
void	image_plane_dimensions(t_mlx *mlx, double *image_plane_width, double *image_plane_height)
{
	double	aspect_ratio_value;

	fov_calculation(mlx->setting->camera, image_plane_width);
	aspect_ratio(mlx, &aspect_ratio_value);
	*image_plane_height = *image_plane_width / aspect_ratio_value;// Calculate image plane height based on the width and aspect ratio
}


//Step 1: Define the Camera's Image Plane
void	camera_image_plane(t_mlx *mlx)
{
	double	image_plane_width;
	double	image_plane_height;

	// Calculate image plane dimensions
	image_plane_dimensions(mlx, &image_plane_width, &image_plane_height);
	printf("Image Plane Width: %f\n", image_plane_width);
	printf("Image Plane Height: %f\n", image_plane_height);

	//TODO Set the camera parameters accordingly
	mlx->setting->camera->image_plane_width = image_plane_width;
	mlx->setting->camera->image_plane_height = image_plane_height;
}


//TODO: this was the entry point
/* There is no need to center the sphere here ... */
void	draw_scene(t_mlx *data)
{
	clock_t	start_time;
	clock_t	end_time;
	//int		i;

	//i = 0;
	//while (i < data->setting->num_spheres)
	//	center_sphere(data->setting->spheres[i++], data->width, data->height);
	//TODO
	camera_image_plane(data);
	start_time = clock();
	cast_rays(data);
	end_time = clock();
	printf("\n\tThe while loop took %s%.2f seconds%s to execute.\n", YELLOW, \
		(((double)end_time - start_time) / CLOCKS_PER_SEC), RESET);
}
