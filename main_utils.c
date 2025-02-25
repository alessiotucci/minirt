/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atucci <atucci@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 16:05:38 by atucci            #+#    #+#             */
/*   Updated: 2025/02/25 17:22:13 by atucci           ###   ########.fr       */
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
	set->check_cam = 0;
	set->check_amb_light = 0;
}

int	missing_elem(t_setting *set)
{
	if (set->check_cam == 0)
		return(error_msg("missing camera in the scene\n"), -42);
	if (set->check_amb_light == 0)
		return(error_msg("missing ambient light in the scene\n"), -42);
	if (set->num_lights == 0)
		return(error_msg("not even a single light in the scene\n"), -42);
	return (0);
}
