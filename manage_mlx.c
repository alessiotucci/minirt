/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_mlx.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atucci <atucci@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 15:39:26 by atucci            #+#    #+#             */
/*   Updated: 2025/02/24 17:12:56 by atucci           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include <time.h>

/* ---------------------- MAIN TEST FUNCTION ---------------------- */
// Format selection status
// Render to screen
// Format camera information
// 5
void	test_function(t_mlx *info)
{
	char	*cam_info;
	char	*selection_status;

	cam_info = camera_info_str(info->setting->camera);
	selection_status = get_selection_status(info->selected);
	mlx_string_put(info->mlx, info->win, 10, info->height - 10,
		COLOR_WHITE, cam_info);
	mlx_string_put(info->mlx, info->win, 10, 10, COLOR_RED, selection_status);
	free(cam_info);
	free(selection_status);
}

// 4
static int	key_pressed(int keycode, void *param)
{
	t_mlx	*help;

	help = (t_mlx *) param;
	if (keycode == ESC)
		clean_close(help);
	else if (keycode == A)
		test_function(help);
	else
		my_key_pressed(keycode, param);
	return (1);
}

// 3
int	window_close(void *param)
{
	t_mlx	*help;

	help = (t_mlx *)param;
	clean_close(help);
	return (0);
}

/*TODO: cast a ray and see if a obj is being intersected*/
// 2
int	mouse_click(int button, int x, int y, t_mlx *mlx)
{
	if (button == 1)
		return (cast_mouse_ray(x, y, mlx, mlx->setting));
	else if (button == 3)
	{
		printf("Mouse: left click [%d][%d]\n", x, y);
		if (is_selected_null(&mlx->selected))
			printf("you haven´t selected an object, cannot translate it\n");
		else
		{
			printf("I am trying translate it to the new point\n");
			perform_translation_from_mouse(mlx, x, y);
			re_start_image(mlx);
		}
	}
	else if ((button == 5) || (button == 4))
		handle_camera_keys(button, mlx);
	test_function(mlx);
	re_start_image(mlx);
	return (0);
}

//TODO: fix the leaks free();
// 1
void	manage_mlx(t_mlx *obj)
{
	obj->mlx = mlx_init();
	ft_printf("%smlx_init has started%s\n", YELLOW, RESET);
	if (obj->mlx == NULL)
		return (ft_putstr_fd("mlx_init fail...\n", 2));
	obj->win = mlx_new_window(obj->mlx, obj->width, obj->height, obj->map_name);
	my_new_image(obj);
	draw_scene(obj);
	mlx_put_image_to_window(obj->mlx, obj->win, obj->img_pointer, 0, 0);
	mlx_mouse_hook(obj->win, mouse_click, obj);
	mlx_hook(obj->win, 2, 1, key_pressed, obj);
	mlx_hook(obj->win, 17, 0L, window_close, obj);
	mlx_loop(obj->mlx);
	mlx_destroy_display(obj->mlx);
	mlx_destroy_window(obj->mlx, obj->win);
}
