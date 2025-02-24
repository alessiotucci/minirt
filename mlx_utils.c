/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atucci <atucci@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 17:12:33 by atucci            #+#    #+#             */
/*   Updated: 2025/02/24 17:16:25 by atucci           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minirt.h"

//3
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

//1
void	re_start_image(t_mlx *data)
{
	mlx_destroy_image(data->mlx, data->img_pointer);
	my_new_image(data);
	draw_scene(data);
	mlx_put_image_to_window(data->mlx, data->win, data->img_pointer, 0, 0);
}

/* This function perfom a clean close and then exit*/
void	clean_close(t_mlx *project)
{
	ft_printf("%sdestroying the windows\n%s\n", RED, RESET);
	mlx_destroy_image(project->mlx, project->img_pointer);
	mlx_destroy_window(project->mlx, project->win);
	mlx_destroy_display(project->mlx);
	free(project->mlx);
	free_struct(project->setting);
	exit(0);
}
