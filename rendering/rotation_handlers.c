/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotation_handlers.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atucci <atucci@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 18:06:36 by atucci            #+#    #+#             */
/*   Updated: 2025/02/19 18:26:33 by atucci           ###   ########.fr       */
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

//5)Rotate the object's axis or normal positively (about the X axis for example).
void	rotate_object_axis_positive(t_mlx *data)
{
	t_plane		*pl;
	t_cylinder	*cy;

	if (data->selected.type == T_PLANE)
	{
		pl = data->setting->planes[data->selected.index];
		pl->normal = rotation_x(pl->normal, ANGLE_DELTA);
	}
	else if (data->selected.type == T_CYLINDER)
	{
		cy = data->setting->cylinders[data->selected.index];
		cy->axis = rotation_x(cy->axis, ANGLE_DELTA);
	}
}

//6)Rotate the object's axis or normal negatively (about the X axis for example).
void	rotate_object_axis_negative(t_mlx *data)
{
	t_plane		*pl;
	t_cylinder	*cy;

	if (data->selected.type == T_PLANE)
	{
		pl = data->setting->planes[data->selected.index];
		pl->normal = rotation_x(pl->normal, -ANGLE_DELTA);
	}
	else if (data->selected.type == T_CYLINDER)
	{
		cy = data->setting->cylinders[data->selected.index];
		cy->axis = rotation_x(cy->axis, -ANGLE_DELTA);
	}
}
