/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_pressed.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atucci <atucci@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 13:56:10 by atucci            #+#    #+#             */
/*   Updated: 2025/02/18 16:30:46 by atucci           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"
// Key codes are defined in your header.
// For example: ARROW_LEFT, ARROW_RIGHT, ARROW_UP, ARROW_DOWN, PLUS, MINUS

void	select_light(t_selected_obj selected)
{
	printf("%sSELECT light!%s\n", YELLOW, RESET);
	selected.index = 0;
	selected.type = T_LIGHT;
}

//3
/* This function perfom a clean close and then exit*/
void	clean_close(t_mlx *project)
{
	ft_printf("%sdestroying the windows\n%s\n", RED, RESET);
	mlx_destroy_window(project->mlx, project->win);
	free_struct(project->setting);
	exit(0);
}
// 44 46
int my_key_pressed(int keycode, void *param)
{
	 t_mlx *data = (t_mlx *)param;

	printf("Keycode; [%d]\n", keycode);
	if (keycode == ARROW_LEFT)
	{
		printf("\n\nMove camera left (modify the x component of the viewpoint)\n");
		data->setting->camera->viewpoint.x -= 2;
	}
	else if (keycode == ARROW_RIGHT)
	{
		data->setting->camera->viewpoint.x += 2;
	}
	else if (keycode == ARROW_UP)
	{
		printf("\n\nMove camera up (modify y component)\n");
		data->setting->camera->viewpoint.y += 2;
	}
	else if (keycode == ARROW_DOWN)
	{
		data->setting->camera->viewpoint.y -= 2;
	}
	else if (keycode == MINUS)
	{
		printf("\n\nZoom in: decrease the FOV to narrow the view\n");
		data->setting->camera->fov -= 5;
		if (data->setting->camera->fov <= 5)
				data->setting->camera->fov = 15;
	}
	else if (keycode == PLUS)
	{
		printf("\n\nZoom out: increase the FOV to widen the view\n");
		data->setting->camera->fov += 5;
		if (data->setting->camera->fov >= 140)
				data->setting->camera->fov = 135;
	}
	else if (keycode == 44)
		data->setting->camera->orientation = rotation_y(data->setting->camera->orientation, M_PI/36);
	else if (keycode == 46)
		data->setting->camera->orientation = rotation_y(data->setting->camera->orientation, -M_PI/36);
	else if (keycode == KEY_L)
		select_light(data->selected);
	else if (is_selected_null(&data->selected) == 0)
		{
			printf("\n\nobject is selected key code to be waited\n");
			if (keycode == KEY_X)
			{
				printf("\n\npressed: X ++increasing radius or diameter (not working with plane)\n");
				increase_object_diameter(data);
			}
			else if (keycode == KEY_Y)
			{
				printf("\n\npressed: Y --decreasing radius or diameter (not working with plane)\n");
				decrease_object_diameter(data);
			}
			else if (keycode == KEY_Z)
			{
				printf("\n\npressed: Z ++increasing height of Cylinder (not compatible with other obj)\n");
				increase_cylinder_height(data);
			}
			else if (keycode == KEY_Q)
			{
				printf("\n\npressed: Q ++increasing height of Cylinder (not compatible with other obj)\n");
					decrease_cylinder_height(data);
			}
			else if (keycode == KEY_W)
			{
				printf("\n\npressed: W inclining the axis (plane or cylinder)\n");
					rotate_object_axis_positive(data);
			}
			else if (keycode == KEY_E)
			{
				printf("\n\npressed: E inclining the axis (plane or cylinder)\n");
					rotate_object_axis_negative(data);
			}
		}
	re_start_image(data);
	return (1);
}

void	re_start_image(t_mlx *data)
{
	if (data->img_pointer)
		mlx_destroy_image(data->mlx, data->img_pointer);
	my_new_image(data);
	draw_scene(data);
	mlx_put_image_to_window(data->mlx, data->win, data->img_pointer, 0, 0);
}

