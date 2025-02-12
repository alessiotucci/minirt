/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_mlx.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atucci <atucci@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 15:39:26 by atucci            #+#    #+#             */
/*   Updated: 2025/02/12 16:49:54 by atucci           ###   ########.fr       */
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
static void	test_function(t_mlx *info)
{
	char	*c;
	char	*strx;
	char	*stry;
	char	*strz;
	char	*str_fov;
	char	*new_str;

	c = "camera : ";
	strx = ft_itoa((int)info->setting->camera->viewpoint.x);
	stry = ft_itoa((int)info->setting->camera->viewpoint.y);
	strz = ft_itoa((int)info->setting->camera->viewpoint.z);
	str_fov= ft_itoa((int)info->setting->camera->fov);
	new_str = ft_strjoin(c, strx);
	new_str = ft_strjoin(new_str, " ");
	new_str = ft_strjoin(new_str, stry);
	new_str = ft_strjoin(new_str, " ");
	new_str = ft_strjoin(new_str, strz);
	new_str = ft_strjoin(new_str, " FOV:");
	new_str = ft_strjoin(new_str, str_fov);

	mlx_string_put(info->mlx, info->win, 10, info->height - 10,
		COLOR_WHITE, new_str);
	if (info->selected_object == NULL)
		mlx_string_put(info->mlx, info->win, 10, 10, COLOR_RED, "selected obj: NULL");
	else
	{
		char *try = type_to_string(info->selected_object->type);
		mlx_string_put(info->mlx, info->win, 10, 10, COLOR_RED, try);
	}
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
	printf("Mouse click: button %d, x = %d, y = %d\n", button, x, y);
	cast_mouse_ray(x, y, mlx, mlx->setting);
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
