/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   centering.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftroise <ftroise@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 15:01:23 by ftroise           #+#    #+#             */
/*   Updated: 2024/12/23 13:36:57 by atucci           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/*
static void	center_viewpoint(t_camera *camera, int window_width, int window_height)
{
	// Calcolo del centro della finestra
	double center_x = window_width / 2.0;
	double center_y = window_height / 2.0;

	// Calcolo delle nuove coordinate del viewpoint
	camera->viewpoint.x = center_x;
	camera->viewpoint.y = center_y;
	camera->viewpoint.z = 0; // L'asse z può essere mantenuto a 0 se non usato
	camera->viewpoint.w = 1; // Assumendo che w sia sempre 1 nel nostro contesto
}

static void	test(t_camera *camera)
{
	// Esempio di utilizzo
	//t_camera camera = {"camera1", {-50.0, 0.0, 20.0, 1.0}, {0.0, 0.0, 0.0, 0.0}, 90};
	//int window_width = 1920;
	//int window_height = 1080;

	// Centrare il viewpoint rispetto alla finestra
	center_viewpoint(camera, DEFAULT_WIDTH, DEFAULT_HEIGHT );
	// Output delle nuove coordinate del viewpoint
	printf("Viewpoint centered:\n");
	printf("x: %lf\n", camera->viewpoint.x);
	printf("y: %lf\n", camera->viewpoint.y);
	printf("z: %lf\n", camera->viewpoint.z);
	printf("w: %lf\n", camera->viewpoint.w);
}

void update_camera(t_mlx *mlx, int x, int y)
{
	mlx->setting->camera->viewpoint.x = (float)x;
	mlx->setting->camera->viewpoint.y = (float)y;
	printf("new coordinate x = %lf, y = %lf\n", mlx->setting->camera->viewpoint.x, mlx->setting->camera->viewpoint.y);
	mlx_destroy_image(mlx->mlx, mlx->img_pointer);
	my_new_image(mlx);
	mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->img_pointer, 0, 0);

}
void	send_to_centre(t_setting *set)
{
	printf("before centering");
	print_vector(set->camera->viewpoint);
	test(set->camera);
}


//TODO: first implementation, need to be worked on
void center_sphere(t_sphere *sphere, int window_width, int window_height)
{
	double	center_x;
	double	center_y;

	center_x = window_width / 2.0;
	center_y = window_height / 2.0;
	sphere->center.x = center_x + sphere->center.x;
	sphere->center.y = center_y - sphere->center.y;
}

*/
