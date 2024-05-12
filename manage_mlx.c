/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_mlx.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atucci <atucci@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 15:39:26 by atucci            #+#    #+#             */
/*   Updated: 2024/05/12 15:48:50 by atucci           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"


void	my_new_image(t_mlx *data)
{

	ft_printf("%sgetting address in img_data%s\n", BG_YELLOW, RESET);
	data->img_pointer = mlx_new_image(data->mlx, data->width,
		data->height);
	data->img_string = mlx_get_data_addr(data->img_pointer, &(data->bits),
		&(data->lsize), &(data->endian));

}
void	my_mlx_pixel_put(t_mlx *data, int x, int y, int color)
{
	char	*dst;

	dst = data->img_string + (y * data->lsize + x * (data->bits / 8));
	*(unsigned int *)dst = color;
}


/* This function perfom a cleana close and then exit*/
static void	clean_close(t_mlx *project)
{
	ft_printf("%sdestroying the windows\n%s\n", RED, RESET);
	mlx_destroy_window(project->mlx, project->win);
	//TODO: free all the memory
	exit(0);
}

static void	test_function(t_mlx *info)
{
	mlx_string_put(info->mlx, info->win, 540, 30, COLOR_GREEN, "key pressed");
}

static int	key_pressed(int keycode, void *param)
{
	t_mlx	*help;

	help = (t_mlx *) param;
	if (keycode == ESC)
		clean_close(help);
	else if (keycode == PLUS)
		test_function(help);
	else if (keycode == MINUS)
		test_function(help);
	else if (keycode == A)
		test_function(help);
	return (1);
}

int	window_close(void *param)
{
	t_mlx	*help;

	help = (t_mlx *)param;
	clean_close(help);
	return (0);
}

/*static void	my_test(t_mlx *obj, t_setting *set)
{

 // Iterate over each pixel
	for (int y = 0; y < obj->height; y++)
	{
		for (int x = 0; x < obj->width; x++)
		{
			// The ray is defined by origin (O) and direction (dir)
			t_vector O = set->camera->orientation;
			t_vector dir = calculate_direction(set->camera, x, y); // You need to implement this function

			// The sphere is defined by its center (C) and radius (r)
			t_vector C = set->spheres[0]->center;
			double r = set->spheres[0]->diameter / 2.0;

			// Calculate the terms of the quadratic equation
			t_vector OC = subtract(O, C);
			double a = dot(dir, dir);
			double b = 2.0 * dot(OC, dir);
			double c = dot(OC, OC) - r*r;

			// Calculate the discriminant
			double discriminant = b*b - 4*a*c;

			// If the discriminant is negative, the ray does not intersect the sphere
			if (discriminant < 0)
			{
				// Color the pixel with the background color
				my_mlx_pixel_put(obj, x, y, COLOR_WHITE);
			}
			else
			{
				// The ray intersects the sphere, color the pixel with the sphere's color
				int color = create_trgb(set->spheres[0]->color);
				my_mlx_pixel_put(obj, x, y, color);
			}
		}
	}
}
*/
void	manage_mlx(t_mlx *obj, t_setting *set)
{
	(void)set; //TODO: just for now
	obj->mlx = mlx_init();
	ft_printf("%smlx_init has started%s\n", YELLOW, RESET);
	if (obj->mlx == NULL)
		return (ft_putstr_fd("mlx_init fail...\n", 2));
	obj->win = mlx_new_window(obj->mlx, obj->width, obj->height, obj->map_name);
	my_new_image(obj);
	//TODO: now draw on the image with some logic
	//my_test(obj, set);
	mlx_put_image_to_window(obj->mlx, obj->win, obj->img_pointer, 0, 0);
	mlx_hook(obj->win, 2, 1, key_pressed, obj);
	mlx_hook(obj->win, 17, 0L, window_close, obj);
	mlx_loop(obj->mlx);
	/*
	mlx_destroy_display();
	mlx_destroy_windows();
	free();
	free();
	*/ //TODO: fix the leaks 
	return ;
}
