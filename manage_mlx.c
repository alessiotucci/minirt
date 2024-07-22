/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_mlx.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftroise <ftroise@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 15:39:26 by atucci            #+#    #+#             */
/*   Updated: 2024/06/18 19:12:57 by ftroise          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"


/*void	my_new_image(t_mlx *data)
{

	ft_printf("%sgetting address in img_data%s\n", BG_YELLOW, RESET);
	data->img_pointer = (data->mlx, data->width,
		data->height);
	data->img_string = mlx_get_data_addr(data->img_pointer, &(data->bits),
		&(data->lsize), &(data->endian));

}*/
void	my_new_image(t_mlx *data)// é la stessa cosa solo che usiamo la funzione mlx_new_imge per creare la finestra ritornando un putatore ad essa 
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

static void	sfondo(t_mlx *data)// t_setting *set)// colora lo sfondo non so se servira ma al moemnto é qualcosa,statica  tanto la usiamo solo qui al momenrto
{
	int			x;
	int			y;
	int		color;
	//int		ray;
	
	y = 0;

	while (y < data->height)
	{
		x = 0;
		while (x < data->width)
		{
			color = (x * 255 / data->width) << 16 | (y * 255 / data->height) << 8; // sfondo multicolore 
			//color = 0xFFFFLL;// sfondo singolo colore
			//ray = create_ray(set -> camera, x, y, data-> width, data->height)
			my_mlx_pixel_put(data, x, y, color);
			x++;
		}
		y++;
	}
	my_mlx_pixel_put(data, data->setting->camera->viewpoint.x, data->setting->camera->viewpoint.y, COLOR_BLACK);
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
/*
void	manage_mlx(t_mlx *obj, t_setting *set)
{
	(void)set; //TODO: just for now
	obj->mlx = mlx_init();
	ft_printf("%smlx_init has started%s\n", YELLOW, RESET);
	if (obj->mlx == NULL)
		return (ft_putstr_fd("mlx_init fail...\n", 2));
	obj->win = mlx_new_window(obj->mlx, obj->width, obj->height, obj->map_name);
	my_new_image(obj);
	//TODO: now draw on the image with some logic
	//my_test(obj, set);
	mlx_put_image_to_window(obj->mlx, obj->win, obj->img_pointer, 0, 0);
	mlx_hook(obj->win, 2, 1, key_pressed, obj);
	mlx_hook(obj->win, 17, 0L, window_close, obj);
	mlx_loop(obj->mlx);
	
	mlx_destroy_display();
	mlx_destroy_windows();
	free();
	free();
	 //TODO: fix the leaks 
	return ;
}*/

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
    sfondo(obj);

    
    mlx_put_image_to_window(obj->mlx, obj->win, obj->img_pointer, 0, 0);
    mlx_mouse_hook(obj->win, mouse_click, obj);
    mlx_hook(obj->win, 2, 1, key_pressed, obj); 
    mlx_hook(obj->win, 17, 0L, window_close, obj); 
    mlx_loop(obj->mlx);
}
