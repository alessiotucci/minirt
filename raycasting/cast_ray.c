/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cast_ray.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atucci <atucci@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/27 13:23:43 by atucci            #+#    #+#             */
/*   Updated: 2025/02/24 17:29:07 by atucci           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

/* new version of the code */
t_ray	create_ray_from_camera2(t_mlx *data, int x, int y)
{
	t_ray		ray;
	t_camera	*cam;
	t_vector	forward;
	t_vector	right;
	t_vector	up;
	t_vector	direction;
	t_vector	temp1;
	t_vector	temp2;
	t_vector	sum;
	double		aspect_ratio;
	double		scale;
	double		ndc_x;
	double		ndc_y;
	double		offset_x;
	double		offset_y;

	cam = data->setting->camera;
	forward = normalization(cam->orientation);
	up = create_vector(0, 1, 0);
	right = cross(forward, up);
	right = normalization(right);
	up = cross(right, forward);
	aspect_ratio = (double)data->width / (double)data->height;
	scale = tan(cam->fov * 0.5 * M_PI / 180.0);
	ndc_x = (x + 0.5) / data->width;
	ndc_y = (y + 0.5) / data->height;
	offset_x = (2 * ndc_x - 1) * aspect_ratio * scale;
	offset_y = (1 - 2 * ndc_y) * scale;
	temp1 = multiplication(right, offset_x);
	temp2 = multiplication(up, offset_y);
	sum = add(temp1, temp2);
	direction = add(sum, forward);
	ray.origin = cam->viewpoint;
	ray.direction = normalization(direction);
	return (ray);
}

/* old version of the code */
t_ray	create_ray_from_camera(t_mlx *data, int x, int y)
{
	t_ray		ray;
	t_vector	direction;
	double		screen_x;
	double		screen_y;
	double		ndc_x;
	double		ndc_y;

	ray.origin = data->setting->camera->viewpoint;
	ndc_x = (x + 0.5) / data->width;
	ndc_y = (y + 0.5) / data->height;
	screen_x = (2 * ndc_x - 1) * data->setting->camera->image_plane_width / 2;
	screen_y = (1 - 2 * ndc_y) * data->setting->camera->image_plane_height / 2;
	direction = create_vector(screen_x, screen_y, -1);
	ray.direction = normalization(direction);
	return (ray);
}

void	cast_rays(t_mlx *data)
{
	int	x;
	int	y;

	y = 0;
	while (y < data->height)
	{
		x = 0;
		while (x < data->width)
		{
			each_pixel_calculation(data, x, y);
			x++;
		}
		y++;
	}
}
