/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   computation.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atucci <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 12:30:04 by atucci            #+#    #+#             */
/*   Updated: 2025/02/05 13:15:30 by atucci           ###   ########.fr       */
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

/*t_color shade_hit(t_setting *world, t_computations comps)
{
    int shadowed;
    t_color final_color;
    t_material m = material(); // Default material

    // Use the over_point (the offset point) for the shadow test.
    shadowed = is_shadowed(world, comps.over_point, *world->lights[0]);

    // Call your lighting function using the over_point.
    final_color = lighting(m,
                           *world->lights[0],
                           comps.over_point,  // Use the offset point!
                           comps.eyev,
                           comps.normalv,
                           shadowed);
    return final_color;
}
*/


t_color shade_hit(t_setting *world, t_computations comps, t_intersection *c_i)
{
    int shadowed;
    t_color final_color;
    //t_material m = material();

    // Use the over_point for shadow testing to avoid acne.
    shadowed = is_shadowed(world, comps.over_point, *world->lights[0]);

    // Compute the final color using the Lambert formula (or both formulas if you later want Phong)
	// object.intesection ?
    final_color = lambert_formula(c_i, *world->lights[0],
                                   comps.over_point, comps.normalv, world);

    // If in shadow, you might reduce the diffuse contribution:
    if (shadowed)
        final_color = multiply_color_by_scalar(get_color_intersect(comps.object), world->amb_light->ratio);

    return final_color;
}

