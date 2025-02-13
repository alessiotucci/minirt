/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_pressed.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atucci <atucci@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 13:56:10 by atucci            #+#    #+#             */
/*   Updated: 2025/02/13 17:36:41 by atucci           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"
// Key codes are defined in your header.
// For example: ARROW_LEFT, ARROW_RIGHT, ARROW_UP, ARROW_DOWN, PLUS, MINUS

//3
/* This function perfom a clean close and then exit*/
void	clean_close(t_mlx *project)
{
	ft_printf("%sdestroying the windows\n%s\n", RED, RESET);
	mlx_destroy_window(project->mlx, project->win);
	free_struct(project->setting);
	exit(0);
}

int key_pressed_gpt(int keycode, void *param)
{
	 t_mlx *data = (t_mlx *)param;

	printf("Keycode; [%d]\n", keycode);
	 // Update the camera based on the key pressed:
	 if (keycode == ARROW_LEFT)
	 {
		  printf("Move camera left (modify the x component of the viewpoint)\n");
		  data->setting->camera->viewpoint.x -= 2; // adjust step size as needed
	 }
	 else if (keycode == ARROW_RIGHT)
	 {
		  data->setting->camera->viewpoint.x += 2;
	 }
	 else if (keycode == ARROW_UP)
	 {
		  printf("Move camera up (modify y component)\n");
		  data->setting->camera->viewpoint.y += 2;
	 }
	 else if (keycode == ARROW_DOWN)
	 {
		  data->setting->camera->viewpoint.y -= 2;
	 }
	 else if (keycode == MINUS)
	 {
		  printf("Zoom in: decrease the FOV to narrow the view\n");
		  data->setting->camera->fov -= 5; // ensure FOV stays within valid range (0, 180)
		  if (data->setting->camera->fov < 1)
				data->setting->camera->fov = 1;
	 }
	 else if (keycode == PLUS)
	 {
		  printf("Zoom out: increase the FOV to widen the view\n");
		  data->setting->camera->fov += 5;
		  if (data->setting->camera->fov > 180)
				data->setting->camera->fov = 180;
	 }
	else if (is_selected_null(data->selected) == 0) // created an helper function to check if null
		{
			printf("object is selected key code to be waited\n");
			if (keycode == KEY_X)
			{
				printf("pressed: X ++increasing radius or diameter (not working with plane)\n");
				increase_object_diameter(data);
			}
			else if (keycode == KEY_Y)
			{
				printf("pressed: Y --decreasing radius or diameter (not working with plane)\n");
				decrease_object_diameter(data);
			}
			else if (keycode == KEY_Z)
			{
				printf("pressed: Z ++increasing height of Cylinder (not compatible with other obj)\n");
				increase_cylinder_height(data);
			}
			else if (keycode == KEY_Q)
			{
				printf("pressed: Q ++increasing height of Cylinder (not compatible with other obj)\n");
					decrease_cylinder_height(data);
			}
			else if (keycode == KEY_W)
			{
				printf("pressed: W inclining the axis (plane or cylinder)\n");
					rotate_object_axis_positive(data);
			}
			else if (keycode == KEY_E)
			{
				printf("pressed: E inclining the axis (plane or cylinder)\n");
					rotate_object_axis_negative(data);
			}
		}
	 // Once the camera is updated, we need to re-render the scene.

	 // (Optional) Destroy the previous image if needed:
//	 if (data->img_pointer)
//	  mlx_destroy_image(data->mlx, data->img_pointer);

	 // Create a new image buffer:
	 // Re-draw the scene:
	 // Update the window with the new image:
	my_new_image(data);
	draw_scene(data);
	mlx_put_image_to_window(data->mlx, data->win, data->img_pointer, 0, 0);
	return (1);
}

