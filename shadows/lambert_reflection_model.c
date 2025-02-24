/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lambert_reflection_model.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atucci <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 15:56:13 by atucci            #+#    #+#             */
/*   Updated: 2025/02/24 18:41:18 by atucci           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

t_color	lambert_lighting(t_setting *world, t_computations comps, t_light light)
{
	t_vector	light_v;
	double		light_dot_normal;
	t_color		ambient;
	t_color		diffuse;
	t_color		base_color;

	base_color = get_color_intersect(comps.object);
	ambient = multiply_color_by_scalar(base_color, world->amb_light->ratio);
	light_v = normalization(subtract(light.position, comps.point));
	if (comps.object.type == T_PLANE)
		light_dot_normal = fabs(dot(light_v, comps.normalv));
	else
		light_dot_normal = dot(light_v, comps.normalv);
	if (light_dot_normal < 0)
		diffuse = create_color(0, 0, 0);
	else
		diffuse = multiply_color_by_scalar(base_color,
				light.brightness * light_dot_normal);
	return (add_colors(ambient, diffuse));
}

/*
else
	diffuse = multiply_color_by_scalar(base_color,
		light.brightness * light_dot_normal);
final_color = add_colors(ambient, diffuse);
*/
