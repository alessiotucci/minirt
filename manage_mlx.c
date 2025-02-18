/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_mlx.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atucci <atucci@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 15:39:26 by atucci            #+#    #+#             */
/*   Updated: 2025/02/17 19:43:35 by atucci           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include <time.h>
//1
void	my_new_image(t_mlx *data)
{
	ft_printf("%sgetting address in img_data%s\n", BG_YELLOW, RESET);
	data->img_pointer = mlx_new_image(data->mlx, data->width, data->height);
	data->img_string = mlx_get_data_addr(data->img_pointer, &(data->bits),
			&(data->lsize), &(data->endian));
}

//2
void	my_mlx_pixel_put(t_mlx *data, int x, int y, int color)
{
	char	*dst;

	dst = data->img_string + (y * data->lsize + x * (data->bits / 8));
	*(unsigned int *)dst = color;
}

//4
//TODO: interesting function!

/* ---------------------- VECTOR FORMATTING ---------------------- */
static char	*vector_to_str(t_vector vec)
{
	char	*x = ft_itoa((int)vec.x);
	char	*y = ft_itoa((int)vec.y);
	char	*z = ft_itoa((int)vec.z);
	char	*temp = ft_strjoin(x, " ");
	char	*temp2 = ft_strjoin(temp, y);
	free(temp);
	temp = ft_strjoin(temp2, " ");
	free(temp2);
	temp2 = ft_strjoin(temp, z);
	free(temp);
	free(x);
	free(y);
	free(z);
	return (temp2);
}

static char	*vector_to_labeled_str(char *label, t_vector vec)
{
	char	*vec_str = vector_to_str(vec);
	char	*full_str = ft_strjoin(label, vec_str);
	free(vec_str);
	return (full_str);
}

/* ---------------------- CAMERA INFO FORMATTING ---------------------- */
static char	*camera_info_str(t_camera *cam)
{
	char	*view_str = vector_to_labeled_str("Camera: ", cam->viewpoint);
	char	*fov_str = ft_strjoin("FOV: ", ft_itoa(cam->fov));
	char	*orient_str = vector_to_labeled_str("| ", cam->orientation);

	char	*final = ft_strjoin(view_str, fov_str);
	free(view_str);
	free(fov_str);

	char	*temp = ft_strjoin(final, orient_str);
	free(final);
	free(orient_str);

	return (temp);
}

/* ---------------------- SELECTION STATUS FORMATTING ---------------------- */
static char	*get_selection_status(t_selected_obj selected)
{
	if (is_selected_null(&selected))
		return (ft_strdup("Selected obj: NULL"));

	const char	*type_str = type_to_string(selected.type);
	char		*buffer = malloc(ft_strlen(type_str) + 15);
	if (buffer)
		sprintf(buffer, "Selected: %s", type_str);
	return (buffer ? buffer : ft_strdup("Selection error"));
}

/* ---------------------- MAIN TEST FUNCTION ---------------------- */
static void	test_function(t_mlx *info)
{
	// Format camera information
	char	*cam_info = camera_info_str(info->setting->camera);

	// Format selection status
	char	*selection_status = get_selection_status(info->selected);

	// Render to screen
	mlx_string_put(info->mlx, info->win, 10, info->height - 10,
		COLOR_WHITE, cam_info);
	mlx_string_put(info->mlx, info->win, 10, 10, COLOR_RED, selection_status);

	// Cleanup
	free(cam_info);
	free(selection_status);
}

static int	key_pressed(int keycode, void *param)
{
	t_mlx	*help;

	help = (t_mlx *) param;
	if (keycode == ESC)
		clean_close(help);
/*	else if (keycode == PLUS)
		test_function(help);
	else if (keycode == MINUS)
		test_function(help);*/
	else if (keycode == A)
		test_function(help);
	else
		key_pressed_gpt(keycode, param);
	return (1);
}

int	window_close(void *param)
{
	t_mlx	*help;

	help = (t_mlx *)param;
	clean_close(help);
	return (0);
}

/*TODO: cast a ray and see if a obj is being intersected*/
int	mouse_click(int button, int x, int y, t_mlx *mlx)
{
//	printf("Mouse click: button %d, x = %d, y = %d\n", button, x, y);
	if (button == 1)
		cast_mouse_ray(x, y, mlx, mlx->setting);
	else if (button == 3)
	{
		printf("Mouse: left click [%d][%d]\n", x, y);
		if (is_selected_null(&mlx->selected))
			printf("you haven´t selected an object, cannot translate it\n");
		else
			printf("I am trying translate it to the new point\n");
	}
	else if (button == 5)
	{
		//printf("Mouse: scroll down not yet implemented\n");
		mlx->setting->camera->orientation = rotation_x(mlx->setting->camera->orientation, M_PI/36);
		re_start_image(mlx);

	}
	else if (button == 4)
	{
		//printf("Mouse: scroll up  not yet implemented\n");
		mlx->setting->camera->orientation = rotation_x(mlx->setting->camera->orientation, -M_PI/36);
		re_start_image(mlx);

	}

	return (0);
}

//TODO: fix the leaks free();
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
//	mlx_hook(obj->win, 2, 1, key_pressed_gpt, obj);
	mlx_hook(obj->win, 17, 0L, window_close, obj);
	mlx_loop(obj->mlx);
	mlx_destroy_display(obj->mlx);
	mlx_destroy_window(obj->mlx, obj->win);
}
