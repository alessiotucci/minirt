/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   computation.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atucci <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 12:30:04 by atucci            #+#    #+#             */
/*   Updated: 2025/02/07 17:12:14 by atucci           ###   ########.fr       */
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
	return (printf("\n\t%sobj type not found!!%s\n\n",RED, RESET), material(d)); // Default material
}

t_computations	prepare_computations(t_intersection i, t_ray r)
{
	t_computations	comps;

	comps.t = i.t;
	comps.object = i.obj;
	// Compute the actual hit point on the surface
	comps.point = position_ray(r, i.t);
	// Offset the hit point slightly along the normal to avoid acne.
	// This over_point is used for shadow testing.
	comps.over_point = add(comps.point, multiplication(comps.normalv, EPSILON));
	// The eye vector is the negation of the ray's direction
	comps.eyev = negate(r.direction);
	// Compute the normal at the hit point
	comps.normalv = v2normal_at(i.obj, comps.point);
		comps.material = get_material(i.obj);
	return (comps);
}


t_color shade_hit(t_setting *world, t_computations comps, int flag)
{
    t_color final_color;
    t_light light = *world->lights[0]; // For example, using the first light.

    // Use the offset over_point for shadow testing.
    int shadowed = is_shadowed(world, comps.over_point, light);

    // Compute the final color based on the chosen lighting model.
    if (!shadowed)
    {
        if (flag)
            final_color = phong_lighting(world, comps, light);
        else
            final_color = lambert_lighting(world, comps, light);
    }
    else
    {
        // If in shadow, only ambient contributes.
        final_color = multiply_color_by_scalar(get_color_intersect(comps.object), world->amb_light->ratio);
    }
    return final_color;
}


t_color	my_lambert_formula(t_intersection *c_i, t_light light, t_vector point, t_vector normal, t_setting *world) // intensity is inside the lights
{
	t_vector	light_v;
	double		light_dot_normal;
	t_color		diffuse;
	t_color		color;

	color = get_color_intersect(c_i->obj);

	(void)world;
	light_v = normalization(subtract(light.position, point));
	if (c_i->obj.type == T_PLANE)
		return (color);
//		light_dot_normal = fabs(dot(light_v, normal));
	else
		light_dot_normal = dot(light_v, normal);
	if (c_i->obj.type == T_PLANE)
		printf("obj.type == T_PLANE\n\tDOUBLE: light_dot_normal: %lf\n", light_dot_normal);
	if (light_dot_normal < 0)
		diffuse = create_color(0, 0, 0);
	else
		diffuse = multiply_color_by_scalar(color, light.brightness * light_dot_normal);
	return (diffuse);
}

t_color	my_shade_hit(t_setting *world, t_computations comps, t_intersection *c_i)
{
	int	shadowed;
	t_color	ambient;
	t_color	diffuse_specular;
	t_color	final_color;


	// Always compute ambient light
	ambient = multiply_color_by_scalar(get_color_intersect(comps.object), world->amb_light->ratio);
	// Compute diffuse only if not shadowed
	shadowed = is_shadowed(world, comps.over_point, *world->lights[0]);
	if (!shadowed)
	{                                                          //TODO: over point?
		diffuse_specular = my_lambert_formula(c_i, *world->lights[0], comps.point, comps.normalv, world);
		//diffuse_specular = phong_lighting(world, comps, *world->lights[0]);(void)c_i;
		final_color = add_colors(ambient, diffuse_specular);
		//final_color = diffuse_specular;
	}
	else
	{
		final_color = ambient; // Only ambient in shadow
	}

	return (final_color);
}
