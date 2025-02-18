/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   translation_handlers.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atucci <atucci@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 20:23:32 by atucci            #+#    #+#             */
/*   Updated: 2025/02/18 13:47:40 by atucci           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

// Clamps a vector's magnitude to a maximum value.
t_vector clamp_delta(t_vector delta, double max_val)
{
	double	mag;
	double	factor;

	mag = magnitude(delta);
	if (mag > max_val)
	{
		factor = max_val / mag;
		return (multiplication(delta, factor));
	}
	return (delta);
}

// Helper function to get the selected object's current position.
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
	{
		printf("Translation not supported for this object type.\n");
		pos = create_vector(0, 0, 0);
	}
	return (pos);
}

// Create a ray through the given pixel using the improved camera function.
// Guard against division by zero if the ray is horizontal.
// Find t such that the ray intersects the horizontal plane at y = reference_y.
// Compute the target point on the plane.
// Compute the delta vector from the current object position to the target point.
t_vector	calculate_translation_delta(t_mlx *mlx, int x, int y, double reference_y, t_vector current_position)
{
	t_ray		ray;
	double		t;
	t_vector	target;
	t_vector	delta;

	ray = create_ray_from_camera2(mlx, x, y);

	if (fabs(ray.direction.y) < EPSILON)
		return create_vector(0, 0, 0);
	t = (reference_y - ray.origin.y) / ray.direction.y;
	target = add(ray.origin, multiplication(ray.direction, t));
	delta = subtract(target, current_position);
    // Apply sensitivity factor.
    delta = multiplication(delta, TRANSLATION_SENSITIVITY);
    // Clamp the delta's magnitude.
    delta = clamp_delta(delta, MAX_DELTA);
	return delta;
}

// Helper function that computes and applies a translation delta based on mouse x, y.
void perform_translation_from_mouse(t_mlx *mlx, int x, int y)
{
	t_vector	current_position;
	double		reference_y;
	t_vector	delta;

	current_position = get_selected_object_position(mlx);
	reference_y = current_position.y;
	delta = calculate_translation_delta(mlx, x, y, reference_y, current_position);
	translate_object(mlx, delta);
	printf("\n\nTranslated object by delta: (%.2f, %.2f, %.2f)\n", delta.x, delta.y, delta.z);
}

void	translate_object(t_mlx *data, t_vector delta)
{
	if (data->selected.type == T_SPHERE)
	{
		t_sphere *sp = data->setting->spheres[data->selected.index];
		sp->center = add(sp->center, delta);
		printf("Sphere center updated to: (%lf, %lf, %lf)\n", sp->center.x, sp->center.y, sp->center.z);
	}
	else if (data->selected.type == T_CYLINDER)
	{
		t_cylinder *cy = data->setting->cylinders[data->selected.index];
		cy->center = add(cy->center, delta);
		printf("Cylinder center updated to: (%lf, %lf, %lf)\n", cy->center.x, cy->center.y, cy->center.z);
	}
	else if (data->selected.type == T_LIGHT)
	{
		t_light *light = data->setting->lights[data->selected.index];
		light->position = add(light->position, delta);
		printf("Light position updated to: (%lf, %lf, %lf)\n", light->position.x, light->position.y, light->position.z);
	}
}
