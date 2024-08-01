/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_mlx.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atucci <atucci@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 15:39:26 by atucci            #+#    #+#             */
/*   Updated: 2024/08/01 15:21:00 by atucci           ###   ########.fr       */
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

//3
/* This function perfom a cleana close and then exit*/
static void	clean_close(t_mlx *project)
{
	ft_printf("%sdestroying the windows\n%s\n", RED, RESET);
	mlx_destroy_window(project->mlx, project->win);
	//TODO: free all the memory
	exit(0);
}

//4
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

int	mouse_click(int button, int x, int y, t_mlx *mlx)
{
	printf("Mouse click: button %d, x = %d, y = %d\n", button, x, y);
	(void)mlx;
	//update_camera(mlx, x, y);
	my_mlx_pixel_put(mlx, x, y, COLOR_GREEN);
	// Qui puoi implementare la logica per reagire al click del mouse
	// Ad esempio, cambiando il colore di un pixel, disegnando qualcosa, ecc.
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

	//send_to_centre(set);
	(void)set;

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
