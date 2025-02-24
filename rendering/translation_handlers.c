/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   translation_handlers.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atucci <atucci@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 20:23:32 by atucci            #+#    #+#             */
/*   Updated: 2025/02/24 17:54:44 by atucci           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

// Helper function to get the selected object's current position.
// 5
t_vector	get_selected_object_position(t_mlx *mlx)
{
	t_vector	pos;

	if (mlx->selected.type == T_SPHERE)
		pos = mlx->setting->spheres[mlx->selected.index]->center;
	else if (mlx->selected.type == T_CYLINDER)
		pos = mlx->setting->cylinders[mlx->selected.index]->center;
	else if (mlx->selected.type == T_LIGHT)
		pos = mlx->setting->lights[mlx->selected.index]->position;
	else
		pos = create_vector(0, 0, 0);
	return (pos);
}

//Create a ray through the mouse coordinates using the improved camera function
//Define the reference plane:
// - Its point is the object's current position
// - Its normal is the camera's orientation
//Compute the target point on the plane
//Compute the delta vector from the object's current position to the target
//Optionally apply a sensitivity factor and clamp the delta
// 4
t_vector	calculate_translation_delta_perp_to_camera(t_mlx *mlx, int x,
				int y, t_vector current_position)
{
	t_ray		ray;
	double		t;
	t_vector	target;
	t_vector	delta;
	double		denom;

	ray = create_ray_from_camera2(mlx, x, y);
	denom = dot(ray.direction, mlx->setting->camera->orientation);
	if (fabs(denom) < EPSILON)
		return (create_vector(0, 0, 0));
	t = -dot(subtract(ray.origin, current_position),
			mlx->setting->camera->orientation) / denom;
	target = add(ray.origin, multiplication(ray.direction, t));
	delta = subtract(target, current_position);
	delta = multiplication(delta, TRANSLATION_SENSITIVITY);
	delta = clamp_delta(delta, MAX_DELTA);
	return (delta);
}

/* Create a ray through the given pixel using the improved camera function.
Guard against division by zero if the ray is horizontal.
Find t such that the ray intersects the horizontal plane at y = reference_y.
Compute the target point on the plane.
Compute the delta vector from the current object position to the target point.
// 3*/
t_vector	calculate_translation_delta(t_mlx *mlx, int x, int y, double reference_y, t_vector current_position)
{
	t_ray		ray;
	double		t;
	t_vector	target;
	t_vector	delta;

	ray = create_ray_from_camera2(mlx, x, y);
	if (fabs(ray.direction.y) < EPSILON)
		return (create_vector(0, 0, 0));
	t = (reference_y - ray.origin.y) / ray.direction.y;
	target = add(ray.origin, multiplication(ray.direction, t));
	delta = subtract(target, current_position);
	delta = multiplication(delta, TRANSLATION_SENSITIVITY);
	delta = clamp_delta(delta, MAX_DELTA);
	return (delta);
}

/*2
 Function that computes and applies a translation delta based on mouse x, y.
*/
void	perform_translation_from_mouse(t_mlx *mlx, int x, int y)
{
	t_vector	current_pos;
	t_vector	d;

	current_pos = get_selected_object_position(mlx);
	d = calculate_translation_delta_perp_to_camera(mlx, x, y, current_pos);
	translate_object(mlx, d);
}

//1
void	translate_object(t_mlx *data, t_vector delta)
{
	t_sphere	*sp;
	t_cylinder	*cy;
	t_light		*light;

	if (data->selected.type == T_SPHERE)
	{
		sp = data->setting->spheres[data->selected.index];
		sp->center = add(sp->center, delta);
	}
	else if (data->selected.type == T_CYLINDER)
	{
		cy = data->setting->cylinders[data->selected.index];
		cy->center = add(cy->center, delta);
	}
	else if (data->selected.type == T_LIGHT)
	{
		light = data->setting->lights[data->selected.index];
		light->position = add(light->position, delta);
	}
}
