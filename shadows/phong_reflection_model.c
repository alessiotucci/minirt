/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   phong_reflection_model.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atucci <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 15:54:36 by atucci            #+#    #+#             */
/*   Updated: 2024/08/01 16:07:09 by atucci           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

t_color	phong_formula(t_material mat, t_light light, t_vector point, t_vector eye, t_vector normal)
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

	effective_color = multiply_colors(mat.color, light.color);
	light_v = normalization(subtract(light.position, point));
	ambient = multiply_color_by_scalar(effective_color, mat.ambient);
	light_dot_normal = dot(light_v, normal);
	if (light_dot_normal < 0)
	{
		//printf("%sDiffuse is black%s\n", BG_RED, BG_RESET);
		//printf("%sSpecular is black%s\n", BG_RED, BG_RESET);
		diffuse = create_color(0, 0, 0);
		specular = create_color(0, 0, 0);
		printf("Light behind the surface. Diffuse and Specular set to black.\n");
	}
	else
	{
		// Diffuse contribution
		diffuse = multiply_color_by_scalar(multiply_color_by_scalar(effective_color, mat.diffuse), light_dot_normal);
		// Reflection vector
		reflect_v = reflect(negate(light_v), normal);
		reflect_dot_eye = dot(reflect_v, eye);
		//printf("Reflect Dot Eye: %lf\n", reflect_dot_eye);
		if (reflect_dot_eye <= 0)
			specular = create_color(0, 0, 0); // black
		else
		{
			// Specular contribution
			factor = pow(reflect_dot_eye, mat.shininess);
			specular = multiply_color_by_scalar(multiply_color_by_scalar(light.color, mat.specular), factor);
		}
	}
	// Final color
	final_color = add_colors(add_colors(ambient, diffuse), specular);
	return (final_color);
}
