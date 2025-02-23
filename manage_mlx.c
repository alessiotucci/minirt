/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_mlx.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atucci <atucci@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 15:39:26 by atucci            #+#    #+#             */
/*   Updated: 2025/02/23 18:12:24 by atucci           ###   ########.fr       */
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
	char	*x;
	char	*y;
	char	*z;
	char	*temp;
	char	*temp2;

	x = ft_itoa((int)vec.x);
	y = ft_itoa((int)vec.y);
	z = ft_itoa((int)vec.z);
	temp = ft_strjoin(x, " ");
	temp2 = ft_strjoin(temp, y);
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
	char	*vec_str;
	char	*full_str;

	vec_str = vector_to_str(vec);
	full_str = ft_strjoin(label, vec_str);
	free(vec_str);
	return (full_str);
}

/* ---------------------- CAMERA INFO FORMATTING ---------------------- */
static char	*camera_info_str(t_camera *cam)
{
	char	*view_str;
	char	*fov_str;
	char	*orient_str;
	char	*temp;
	char	*final;

	view_str = vector_to_labeled_str("Camera: ", cam->viewpoint);
	fov_str = ft_strjoin("FOV: ", ft_itoa(cam->fov));
	orient_str = vector_to_labeled_str("| ", cam->orientation);
	final = ft_strjoin(view_str, fov_str);
	free(view_str);
	free(fov_str);
	temp = ft_strjoin(final, orient_str);
	free(final);
	free(orient_str);
	return (temp);
}

void	my_sprintf(char *buffer, char *key, char *old_value, char *new_value)
{
	int	bufflen;

	bufflen = ft_strlen(buffer);
	ft_strlcpy(buffer, key, ft_strlen(key) + 1);
	ft_strlcat(buffer, "=", bufflen + 2);
	if (old_value != NULL)
		ft_strlcat(buffer, old_value, ft_strlen(old_value) + bufflen + 1);
	ft_strlcat(buffer, new_value, ft_strlen(new_value) + bufflen + 1);
}

/* ---------------------- SELECTION STATUS FORMATTING ---------------------- */
static char	*get_selection_status(t_selected_obj selected)
{
	const char	*type_str;
	char		*buffer;
	char		*full_str;

	if (is_selected_null(&selected))
		return (ft_strdup("Selected obj: NULL"));
	type_str = type_to_string(selected.type);
	full_str = ft_strjoin("Selected: ", type_str);
	if (!full_str)
		return (ft_strdup("Selection error"));
	buffer = malloc(ft_strlen(full_str) + 1);
	if (!buffer)
		return (free(full_str), ft_strdup("Selection error"));
	my_sprintf(buffer, full_str, "", "");
	free(full_str);
	return (buffer);
}



/* ---------------------- MAIN TEST FUNCTION ---------------------- */
// Format selection status
// Render to screen
// Format camera information
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
