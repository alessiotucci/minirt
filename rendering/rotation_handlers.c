/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotation_handlers.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atucci <atucci@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 18:06:36 by atucci            #+#    #+#             */
/*   Updated: 2025/02/24 17:50:17 by atucci           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

//3)Increase the height of a cylinder.
void	increase_cylinder_height(t_mlx *data)
{
	t_cylinder	*cy;

	if (data->selected.type == T_CYLINDER)
	{
		cy = data->setting->cylinders[data->selected.index];
		cy->height += HEIGHT_DELTA;
		update_cylinder(cy);
	}
}

//4)Decrease the height of a cylinder.
void	decrease_cylinder_height(t_mlx *data)
{
	t_cylinder	*cy;

	if (data->selected.type == T_CYLINDER)
	{
		cy = data->setting->cylinders[data->selected.index];
		cy->height -= HEIGHT_DELTA;
		update_cylinder(cy);
		if (cy->height < 1.0)
			cy->height = 1.0;
	}
}

//5)Rotate the object's axis or normal positively about the X axis for example
void	rotate_object_axis_positive(t_mlx *data)
{
	t_plane		*pl;
	t_cylinder	*cy;

	if (data->selected.type == T_PLANE)
	{
		pl = data->setting->planes[data->selected.index];
		pl->normal = rotation_x(pl->normal, (M_PI / 36));
	}
	else if (data->selected.type == T_CYLINDER)
	{
		cy = data->setting->cylinders[data->selected.index];
		cy->axis = rotation_x(cy->axis, (M_PI / 36));
	}
}

//6)Rotate the object's axis or normal negatively about the X axis for example
void	rotate_object_axis_negative(t_mlx *data)
{
	t_plane		*pl;
	t_cylinder	*cy;

	if (data->selected.type == T_PLANE)
	{
		pl = data->setting->planes[data->selected.index];
		pl->normal = rotation_x(pl->normal, -(M_PI / 36));
	}
	else if (data->selected.type == T_CYLINDER)
	{
		cy = data->setting->cylinders[data->selected.index];
		cy->axis = rotation_x(cy->axis, -(M_PI / 36));
	}
}
