/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lambert_reflection_model.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atucci <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 15:56:13 by atucci            #+#    #+#             */
/*   Updated: 2025/02/08 16:37:01 by atucci           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

t_color lambert_lighting(t_setting *world, t_computations comps, t_light light)
{
	t_vector light_v;
	double	 light_dot_normal;
	t_color	ambient;
	t_color	diffuse;
	t_color	base_color;
	t_color	final_color;

	// Get the object's color
	base_color = get_color_intersect(comps.object);

	// Ambient contribution:
	ambient = multiply_color_by_scalar(base_color, world->amb_light->ratio);

	// Compute the light vector from the hit point (using the actual point for lighting)
	light_v = normalization(subtract(light.position, comps.point));

	// For diffuse shading: if the object is a plane, use fabs to ensure non-negative dot product.
	if (comps.object.type == T_PLANE)
		return (base_color);
//		light_dot_normal = fabs(dot(light_v, comps.normalv));
	else
		light_dot_normal = dot(light_v, comps.normalv);

	if (light_dot_normal < 0)
		diffuse = create_color(0, 0, 0);
	else
		diffuse = multiply_color_by_scalar(base_color, light.brightness * light_dot_normal);

	// Final color is the sum of ambient and diffuse.
	final_color = add_colors(ambient, diffuse);
	return final_color;
}

