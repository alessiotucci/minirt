/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   phong_reflection_model.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atucci <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 15:54:36 by atucci            #+#    #+#             */
/*   Updated: 2025/02/23 18:10:24 by atucci           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

/****************************************************************************/
/*TODO: make a comparison between Lambert and Phong, with parameters        */
/****************************************************************************/
/*
t_color phong_lighting(t_setting *world, t_computations comps, t_light light)
{
	t_color		effective_color;
	t_vector	light_v;
	t_color		ambient;
	double		light_dot_normal;
	t_color		diffuse;
	t_color		specular;
	t_vector	reflect_v;
	double		reflect_dot_eye;
	double		factor;
	t_color		final_color;

	effective_color = multiply_colors(get_color_intersect(comps.object),
	light.color);
	ambient = multiply_color_by_scalar(effective_color, world->amb_light->ratio
	* comps.material.ambient);
	light_v = normalization(subtract(light.position, comps.point));
	light_dot_normal = (comps.object.type == T_PLANE)
	? fabs(dot(light_v, comps.normalv)) : dot(light_v, comps.normalv);
	if (light_dot_normal > 0)
		diffuse = multiply_color_by_scalar(effective_color,
		comps.material.diffuse * light_dot_normal);
	else
		diffuse = create_color(0, 0, 0);
	reflect_v = reflect(negate(light_v), comps.normalv);
	reflect_dot_eye = dot(reflect_v, comps.eyev);
	if (reflect_dot_eye > 0)
	{
		factor = pow(reflect_dot_eye, comps.material.shininess);
		specular = multiply_color_by_scalar(light.color,
		comps.material.specular * factor);
	}
	else
		specular = create_color(0, 0, 0);
	final_color = add_colors(add_colors(ambient, diffuse), specular);
	return (final_color);
}
*/
