/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   computation.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atucci <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 12:30:04 by atucci            #+#    #+#             */
/*   Updated: 2025/02/06 19:52:42 by atucci           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minirt.h"

t_computations prepare_computations(t_intersection i, t_ray r)
{
    t_computations comps;

    comps.t = i.t;
    comps.object = i.obj;
    // Compute the actual hit point on the surface
    comps.point = position_ray(r, i.t);
    // The eye vector is the negation of the ray's direction
    comps.eyev = negate(r.direction);
    // Compute the normal at the hit point
    comps.normalv = v2normal_at(i.obj, comps.point);

    // Offset the hit point slightly along the normal to avoid acne.
    // This over_point is used for shadow testing.
    comps.over_point = add(comps.point, multiplication(comps.normalv, EPSILON));

    return comps;
}


/*
t_color shade_hit(t_setting *world, t_computations comps, t_intersection *c_i, t_vector eye)
{
    int shadowed;(void)shadowed;
    t_color final_color;
    t_material m = material();(void)m; (void)eye;(void)c_i;
    // Use the over_point for shadow testing to avoid acne.
    shadowed = is_shadowed(world, comps.over_point, *world->lights[0]);

    // Compute the final color using the Lambert formula (or both formulas if you later want Phong)
	// object.intesection ?
    final_color = lambert_formula(c_i, *world->lights[0], comps.over_point, comps.normalv, world);
    //final_color = phong_lighting(m, *world->lights[0], comps.over_point, comps.eyev, comps.normalv);
	//TODO:
    // If in shadow, you might reduce the diffuse contribution:
    if (shadowed)
        final_color = multiply_color_by_scalar(get_color_intersect(comps.object), world->amb_light->ratio);

    return final_color;
}
*/

t_color	shade_hit(t_setting *world, t_computations comps, t_intersection *c_i, t_vector eye)
{
	int	shadowed;
	t_color	ambient;
	t_color	diffuse_specular;
	t_color	final_color;

	(void)eye; (void)c_i;

	// Always compute ambient light
	ambient = multiply_color_by_scalar(get_color_intersect(comps.object), world->amb_light->ratio);

	// Compute diffuse only if not shadowed
	shadowed = is_shadowed(world, comps.over_point, *world->lights[0]);
	printf("shadowed: [%d]\n", shadowed);
	if (!shadowed)
	{                                                          //TODO: over point?
		diffuse_specular = lambert_formula(c_i, *world->lights[0], comps.point, comps.normalv, world);
		final_color = add_colors(ambient, diffuse_specular);
		//final_color = diffuse_specular;
	}
	else
	{
		final_color = ambient; // Only ambient in shadow
	}

	return (final_color);
}
