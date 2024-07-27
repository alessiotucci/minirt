/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_scene.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atucci <atucci@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/27 13:24:15 by atucci            #+#    #+#             */
/*   Updated: 2024/07/27 13:35:27 by atucci           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

#include <time.h>
void	draw_scene(t_mlx *data)
{
	clock_t	start_time;
	clock_t	end_time;
	double	time_taken;
	int		i;

	i = 0;
	while (i < data->setting->num_spheres)
	{
		center_sphere(data->setting->spheres[i], data->width, data->height);
		i++;
	}
	start_time = clock();
	cast_rays(data);
	end_time = clock();
	time_taken = ((double)end_time - start_time) / CLOCKS_PER_SEC;
	printf("\n\tThe while loop took %s%.2f seconds%s to execute.\n", YELLOW, time_taken, RESET);
}
