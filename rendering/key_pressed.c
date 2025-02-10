/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_pressed.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atucci <atucci@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 13:56:10 by atucci            #+#    #+#             */
/*   Updated: 2025/02/10 14:28:03 by atucci           ###   ########.fr       */
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
        data->setting->camera->viewpoint.x -= 5; // adjust step size as needed
    }
    else if (keycode == ARROW_RIGHT)
    {
        data->setting->camera->viewpoint.x += 5;
    }
    else if (keycode == ARROW_UP)
    {
        printf("Move camera up (modify y component)\n");
        data->setting->camera->viewpoint.y += 5;
    }
    else if (keycode == ARROW_DOWN)
    {
        data->setting->camera->viewpoint.y -= 5;
    }
    else if (keycode == PLUS)
    {
        printf("Zoom in: decrease the FOV to narrow the view\n");
        data->setting->camera->fov -= 5; // ensure FOV stays within valid range (0, 180)
        if (data->setting->camera->fov < 1)
            data->setting->camera->fov = 1;
    }
    else if (keycode == MINUS)
    {
        printf("Zoom out: increase the FOV to widen the view\n");
        data->setting->camera->fov += 5;
        if (data->setting->camera->fov > 180)
            data->setting->camera->fov = 180;
    }
    else if (keycode == ESC)
    {
        clean_close(data);
        return (0);
    }
	else
		printf("stupido cojone\n");

    // Once the camera is updated, we need to re-render the scene.

    // (Optional) Destroy the previous image if needed:
//    if (data->img_pointer)
//     mlx_destroy_image(data->mlx, data->img_pointer);

    // Create a new image buffer:
    my_new_image(data);

    // Re-draw the scene:
    draw_scene(data);

    // Update the window with the new image:
    mlx_put_image_to_window(data->mlx, data->win, data->img_pointer, 0, 0);

    return (1);
}

