/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lambert_reflection_model.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atucci <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 15:56:13 by atucci            #+#    #+#             */
/*   Updated: 2024/09/28 15:06:24 by atucci           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

//material is part of phong, it is bonus and it is not mentioned in mandatory part
t_color	lambert_formula(t_intersection *c_i, t_light light, t_vector point, t_vector normal) // intensity is inside the lights
{
	t_vector	light_v;
	double		light_dot_normal;
	t_color		diffuse;
	t_color		color;

	color = get_color_intersect(c_i->obj);
	if (c_i->obj.type == T_PLANE)
		return (color);
	//printf("VECTOR: light.position\n");
	//print_vector(light.position);
	//printf("VECTOR: point\n");
	//print_vector(point);
	light_v = normalization(subtract(light.position, point));
	//printf("VECTOR: light_v\n");
	//print_vector(light_v);
	//printf("VECTOR: normal\n");
	//print_vector(normal);
	
	light_dot_normal = dot(light_v, normal);
	/*if (c_i->obj.type != T_PLANE)
		light_dot_normal = dot(light_v, normal);
	else
		light_dot_normal = fabs(dot(light_v, normal));*/

	//printf("DOUBLE: light_dot_normal: %lf\n", light_dot_normal);
	if (light_dot_normal < 0)
	{
		diffuse = create_color(0, 0, 0);
		//printf("lambert still black\n");
	}
	else
		diffuse = multiply_color_by_scalar(color, light.brightness * light_dot_normal);
	return (diffuse);
}
