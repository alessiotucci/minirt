/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_mlx.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atucci <atucci@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 15:39:26 by atucci            #+#    #+#             */
/*   Updated: 2024/07/26 17:59:53 by atucci           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include <time.h>

//TODO I want too see how long it going to take

/*void	my_new_image(t_mlx *data)
{

	ft_printf("%sgetting address in img_data%s\n", BG_YELLOW, RESET);
	data->img_pointer = (data->mlx, data->width,
		data->height);
	data->img_string = mlx_get_data_addr(data->img_pointer, &(data->bits),
		&(data->lsize), &(data->endian));

}*/

void	my_new_image(t_mlx *data)
{
	ft_printf("%sgetting address in img_data%s\n", BG_YELLOW, RESET);
	data->img_pointer = mlx_new_image(data->mlx, data->width, data->height);
	data->img_string = mlx_get_data_addr(data->img_pointer, &(data->bits),
		&(data->lsize), &(data->endian));
}

void	my_mlx_pixel_put(t_mlx *data, int x, int y, int color)
{
	char	*dst;

	dst = data->img_string + (y * data->lsize + x * (data->bits / 8));
	*(unsigned int *)dst = color;
}

//TODO: to be deleted
void	wallpaper(t_mlx *data)
{
	int			x;
	int			y;
	int		color;
	//int		ray;
	
	clock_t start_time = clock();
	y = 0;

	while (y < data->height)
	{
		x = 0;
		while (x < data->width)
		{
			//color = (x * 255 / data->width) << 16 | (y * 255 / data->height) << 8;
			color = 0xFFFFLL;
			//TODO: here I supposed to cast a ray to see if there is a intersection
			my_mlx_pixel_put(data, x, y, color);
			x++;
		}
		y++;
	}
	my_mlx_pixel_put(data, data->setting->camera->viewpoint.x, data->setting->camera->viewpoint.y, COLOR_BLACK);

	clock_t end_time = clock();
	double time_taken = ((double)end_time - start_time) / CLOCKS_PER_SEC;
	printf("\n\tThe while loop took %s%.2f seconds%s to execute.\n", YELLOW, time_taken, RESET);
}

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
	printf("\n%sDEBUG HERE:%s create_ray_from_camera/manage_mlx.c\n", YELLOW, RESET);
	ray.direction = normalization(create_vector(x - width / 2.0, height / 2.0 - y, camera->orientation.z));
	return (ray);
}

int	calculate_sphere_color(t_intersection *intersection)
{
	t_sphere	*sphere;

	sphere = (t_sphere *)intersection->obj.obj;
	return (create_trgb(sphere->color));
}
//TODO: LAST VERSION OF GPT
/*
 *void cast_rays(t_mlx *data) {
    int x, y;
    t_ray ray;
    t_intersection_list *all_intersections;
    t_intersection *closest_intersection;

    for (y = 0; y < data->height; y++) {
        for (x = 0; x < data->width; x++) {
            ray = create_ray_from_camera(data->setting->camera, x, y, data->width, data->height);
            all_intersections = malloc(sizeof(t_intersection_list));
            all_intersections->count = 0;
            all_intersections->intersections = malloc(sizeof(t_intersection) * data->setting->num_spheres * 2);

            for (int i = 0; i < data->setting->num_spheres; i++) {
                t_intersection_list *sphere_intersections = intersect_sphere(*data->setting->spheres[i], ray);
                if (sphere_intersections) {
                    add_intersections_to_list(all_intersections, sphere_intersections);
                }
            }

            closest_intersection = hit(all_intersections);
            if (closest_intersection != NULL) {
                my_mlx_pixel_put(data, x, y, calculate_sphere_color(closest_intersection));
            } else {
                my_mlx_pixel_put(data, x, y, 0x000000);  // Background color
            }

            free(all_intersections->intersections);
            free(all_intersections);
        }
    }
}
 */
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

void	draw_scene(t_mlx *data)
{
	clock_t	start_time;
	clock_t	end_time;
	double	time_taken;
	int		i;

	i = 0;
	while (i < data->setting->num_spheres)
	{
		center_sphere(data->setting->spheres[i], data->width, data->height);
		i++;
	}
	start_time = clock();
	cast_rays(data);
	end_time = clock();
	time_taken = ((double)end_time - start_time) / CLOCKS_PER_SEC;
	printf("\n\tThe while loop took %s%.2f seconds%s to execute.\n", YELLOW, time_taken, RESET);
}


/* This function perfom a cleana close and then exit*/
static void	clean_close(t_mlx *project)
{
	ft_printf("%sdestroying the windows\n%s\n", RED, RESET);
	mlx_destroy_window(project->mlx, project->win);
	//TODO: free all the memory
	exit(0);
}

//TODO: interesting function!
static void	test_function(t_mlx *info)
{
	char c[] = "camera : "; 
	char *strx = ft_itoa((int)info->setting->camera->viewpoint.x);
	char *stry = ft_itoa((int)info->setting->camera->viewpoint.y);

	char *new_str = ft_strjoin(c, strx);
	new_str = ft_strjoin(new_str, "   ");
	new_str = ft_strjoin(new_str, stry);
	//TODO: The commented line would center the text
	//mlx_string_put(info->mlx, info->win, info->width / 2, info->height / 2, COLOR_WHITE, "camera: ");
	mlx_string_put(info->mlx, info->win, 10, info->height - 10, COLOR_RED, new_str);
	mlx_string_put(info->mlx, info->win, 10, 10, COLOR_RED, "selected obj: ");
}

static int	key_pressed(int keycode, void *param)
{
	t_mlx	*help;

	help = (t_mlx *) param;
	if (keycode == ESC)
		clean_close(help);
//	else if (keycode == PLUS)
//		test_function(help);
//	else if (keycode == MINUS)
//		test_function(help);
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

void manage_mlx(t_mlx *obj, t_setting *set)
{
	obj->mlx = mlx_init();
	ft_printf("%smlx_init has started%s\n", YELLOW, RESET);
	if (obj->mlx == NULL)
		return (ft_putstr_fd("mlx_init fail...\n", 2));
	obj->win = mlx_new_window(obj->mlx, obj->width, obj->height, obj->map_name);
	my_new_image(obj); 

	send_to_centre(set);

	// Disegna la scena
	//wallpaper(obj);
	draw_scene(obj);
	mlx_put_image_to_window(obj->mlx, obj->win, obj->img_pointer, 0, 0);
	mlx_mouse_hook(obj->win, mouse_click, obj);
	mlx_hook(obj->win, 2, 1, key_pressed, obj); 
	mlx_hook(obj->win, 17, 0L, window_close, obj); 
	mlx_loop(obj->mlx);
	mlx_destroy_display(obj->mlx);
	mlx_destroy_window(obj->mlx, obj->win);
	//TODO: fix the leaks free();

}
