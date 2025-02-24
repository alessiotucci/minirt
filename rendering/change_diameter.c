/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   change_diameter.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atucci <atucci@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 16:41:11 by atucci            #+#    #+#             */
/*   Updated: 2025/02/24 16:48:18 by atucci           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

//1)Increase the diameter (for spheres and cylinders)
void	increase_object_diameter(t_mlx *data)
{
	t_sphere	*sp;
	t_cylinder	*cy;

	if (data->selected.type == T_SPHERE)
	{
		sp = data->setting->spheres[data->selected.index];
		sp->diameter += DIAMETER_DELTA;
	}
	else if (data->selected.type == T_CYLINDER)
	{
		cy = data->setting->cylinders[data->selected.index];
		cy->diameter += DIAMETER_DELTA;
	}
}

//2)Decrease the diameter (for spheres and cylinders)
void	decrease_object_diameter(t_mlx *data)
{
	t_sphere	*sp;
	t_cylinder	*cy;

	if (data->selected.type == T_SPHERE)
	{
		sp = data->setting->spheres[data->selected.index];
		sp->diameter -= DIAMETER_DELTA;
		if (sp->diameter <= 1)
			sp->diameter = 1;
	}
	else if (data->selected.type == T_CYLINDER)
	{
		cy = data->setting->cylinders[data->selected.index];
		cy->diameter -= DIAMETER_DELTA;
		if (cy->diameter <= 1)
			cy->diameter = 1;
	}
}
