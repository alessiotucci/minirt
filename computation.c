/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   computation.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atucci <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 12:30:04 by atucci            #+#    #+#             */
/*   Updated: 2025/02/18 18:18:36 by atucci           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minirt.h"

// Helper function to get material from object
static t_material get_material(t_object obj)
{
	t_color	d;

	d = create_color(0, 0, 0);
	if (obj.type == T_SPHERE)
		return ((t_sphere *)obj.address)->material;
	if (obj.type == T_PLANE)
		return ((t_plane *)obj.address)->material;
	if (obj.type == T_CYLINDER)
		return ((t_cylinder *)obj.address)->material;
	return (printf("\n\t%sobj type not found!%s\n\n",RED, RESET), material(d));
}

/*
 Compute the actual hit point on the surface
 Offset the hit point slightly along the normal to avoid acne.
 This over_point is used for shadow testing.
 The eye vector is the negation of the ray's direction
 Compute the normal at the hit point
*/
t_computations	prepare_computations(t_intersection i, t_ray r)
{
	t_computations	comps;

	comps.t = i.t;
	comps.object = i.obj;
	comps.point = position_ray(r, i.t);
	comps.over_point = add(comps.point, multiplication(comps.normalv, EPSILON));
	comps.eyev = negate(r.direction);
	comps.normalv = v2normal_at(i.obj, comps.point, r);
	comps.material = get_material(i.obj);
	return (comps);
}

//TODO: check wheter you can use multiple light sources
// Use the offset over_point for shadow testing.
// Compute the final color based on the chosen lighting model.
t_color	shade_hit(t_setting *world, t_computations comps, int flag)
{
	t_color	final_color;
	t_light	light;
	int	shadowed;

	light = *world->lights[0];
	shadowed = is_shadowed(world, comps.over_point, light);
	if (!shadowed)
	{
		if (flag)
			final_color = phong_lighting(world, comps, light);
		else
			final_color = lambert_lighting(world, comps, light);
	}
	else
		final_color = multiply_color_by_scalar(get_color_intersect(comps.object), world->amb_light->ratio);
	return final_color;
}
