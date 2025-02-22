/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_pressed.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atucci <atucci@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 13:56:10 by atucci            #+#    #+#             */
/*   Updated: 2025/02/22 13:52:22 by atucci           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

//7
// Key codes are defined in your header.
// For example: ARROW_LEFT, ARROW_RIGHT, ARROW_UP, ARROW_DOWN, PLUS, MINUS
void	select_light(t_selected_obj *selected)
{
	printf("%sSELECT light!%s\n", YELLOW, RESET);
	selected->index = 0;
	selected->type = T_LIGHT;
}

//6
/* This function perfom a clean close and then exit*/
void	clean_close(t_mlx *project)
{
	ft_printf("%sdestroying the windows\n%s\n", RED, RESET);
	mlx_destroy_image(project->mlx, project->img_pointer);
	mlx_destroy_window(project->mlx, project->win);
	// destroy display
	mlx_destroy_display(project->mlx);
	free(project->mlx);
	free_struct(project->setting);
	exit(0);
}

//5
void	handle_plus_minus(int keycode, t_mlx *data)
{
	if (keycode == MINUS)
	{
		printf("Zoom in: decrease the FOV to narrow the view\n");
		data->setting->camera->fov -= 5;
		if (data->setting->camera->fov <= 5)
			data->setting->camera->fov = 15;
	}
	else if (keycode == PLUS)
	{
		printf("Zoom out: increase the FOV to widen the view\n");
		data->setting->camera->fov += 5;
		if (data->setting->camera->fov >= 140)
			data->setting->camera->fov = 135;
	}
}

//4 Handles camera movement, zoom, and tilting.
void	handle_camera_keys(int keycode, t_mlx *data)
{
	t_vector	o;

	o = data->setting->camera->orientation;
	if (keycode == ARROW_LEFT)
		data->setting->camera->viewpoint.x -= 2;
	else if (keycode == ARROW_RIGHT)
		data->setting->camera->viewpoint.x += 2;
	else if (keycode == ARROW_UP)
		data->setting->camera->viewpoint.y += 2;
	else if (keycode == ARROW_DOWN)
		data->setting->camera->viewpoint.y -= 2;
	else if (keycode == PLUS || keycode == MINUS)
		handle_plus_minus(keycode, data);
	else if (keycode == 44)
		data->setting->camera->orientation = rotation_y(o, M_PI / 36);
	else if (keycode == 46)
		data->setting->camera->orientation = rotation_y(o, -M_PI / 36);
	else if (keycode == 5)
		data->setting->camera->orientation = rotation_x(o, M_PI / 36);
	else if (keycode == 4)
		data->setting->camera->orientation = rotation_x(o, -M_PI / 36);
	print_camera(data->setting->camera);
}

//3 Handles object-specific transformation keys.
void	handle_object_keys(int keycode, t_mlx *data)
{
	if (keycode == KEY_X)
		increase_object_diameter(data);
	else if (keycode == KEY_Y)
		decrease_object_diameter(data);
	else if (keycode == KEY_Z)
		increase_cylinder_height(data);
	else if (keycode == KEY_Q)
		decrease_cylinder_height(data);
	else if (keycode == KEY_W)
		rotate_object_axis_positive(data);
	else if (keycode == KEY_E)
		rotate_object_axis_negative(data);
	else if (keycode == KEY_L)
		select_light(&data->selected);
}

//2 Main key press handler.
int	my_key_pressed(int keycode, void *param)
{
	t_mlx	*data;

	data = (t_mlx *)param;
	printf("Keycode: [%d]\n", keycode);
	if (keycode == ARROW_LEFT || keycode == ARROW_RIGHT
		|| keycode == ARROW_UP || keycode == ARROW_DOWN
		|| keycode == MINUS || keycode == PLUS
		|| keycode == 44 || keycode == 46)
	{
		handle_camera_keys(keycode, data);
	}
	else if (!is_selected_null(&data->selected))
		handle_object_keys(keycode, data);
	else
		printf("No object selected; camera remains unchanged.\n");
	test_function(data);
	re_start_image(data);
	mlx_put_image_to_window(data->mlx, data->win, data->img_pointer, 0, 0);
	return (1);
}

//1
void	re_start_image(t_mlx *data)
{
//	if (data->img_pointer)
	mlx_destroy_image(data->mlx, data->img_pointer);
	my_new_image(data);
	draw_scene(data);
	mlx_put_image_to_window(data->mlx, data->win, data->img_pointer, 0, 0);
}
