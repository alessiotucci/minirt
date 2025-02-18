/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   translation_handlers.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atucci <atucci@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 20:23:32 by atucci            #+#    #+#             */
/*   Updated: 2025/02/17 20:30:43 by atucci           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

void	translate_object(t_mlx *data, t_vector delta)
{
	double	**translation;
	double	**new_transform;
	t_sphere	*sp;
	t_cylinder	*cy;

	if (data->selected.type == T_SPHERE)
	{
		sp = data->setting->spheres[data->selected.index];
		translation = create_translation_matrix(delta);
		new_transform = multiply_matrix(4, 4, translation, sp->transform);
		free_heap_matrix(sp->transform, 4);
		sp->transform = new_transform;
		//update_object_transform(&data->selected);
		free_heap_matrix(translation, 4);
	}
	else if (data->selected.type == T_CYLINDER)
	{
		cy = data->setting->cylinders[data->selected.index];
		translation = create_translation_matrix(delta);
		new_transform = multiply_matrix(4, 4, translation, cy->transform);
		free_heap_matrix(cy->transform, 4);
		cy->transform = new_transform;
		//update_object_transform(&data->selected);
		free_heap_matrix(translation, 4);
	}
	// Add other object types similarly
}
