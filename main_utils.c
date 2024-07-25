/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atucci <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 16:05:38 by atucci            #+#    #+#             */
/*   Updated: 2024/07/25 16:06:05 by atucci           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minirt.h"

void	error_msg(char *str)
{
	ft_printf("error\n");
	ft_printf("Minirt: %s%s%s", RED, str, RESET);
}

/* function to set the counter of object in the setting to zero */
void	setback_zero(t_setting *set)
{
		set->num_lights = 0;
		set->num_spheres = 0;
		set->num_planes = 0;
		set->num_cylinders = 0;
		set->num_cones = 0;
}

void	init_scene(t_mlx *info, char *mapname)
{
	info->width = DEFAULT_WIDTH;
	info->height = DEFAULT_HEIGHT;
	info->map_name = mapname;
}


