/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   normal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atucci <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 14:24:11 by atucci            #+#    #+#             */
/*   Updated: 2025/02/18 19:12:50 by atucci           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

//REASON  gpt
// Get the stored normal.
// If the dot product between the ray's direction and the normal is positive,
// then the ray is coming from behind the plane.
// Flip the normal so that it faces the ray.
static t_vector	get_plane_normal(t_plane *pl, t_ray ray)
{
	t_vector	normal;

	normal = pl->normal;
	if (dot(ray.direction, normal) > 0)
		normal = multiplication(normal, -1);
	return (normal);
}

//reason by gpt
// Subtract the cylinder’s center (for the XZ coordinates)
t_vector	local_point_in_cylinder(t_cylinder *cylinder, t_vector point)
{
	t_vector	local;

	local.x = point.x - cylinder->center.x;
	local.y = point.y;
	local.z = point.z - cylinder->center.z;
	local.w = point.w;
	return (local);
}

//TODO:
t_vector	default_cylinder_normal(t_cylinder *cylinder, t_vector point)
{
	t_vector	local;
	double		r_squared;
	double		dist_xz;

	local = local_point_in_cylinder(cylinder, point);
	r_squared = pow(cylinder->diameter / 2, 2);
	dist_xz = pow(local.x, 2) + pow(local.z, 2);
	if (dist_xz < r_squared)
	{
		if (comparing_double(local.y, cylinder->max))
			return (create_vector(0, 1, 0));
		else if (comparing_double(local.y, cylinder->min))
			return (create_vector(0, -1, 0));
	}
	return (normalization(create_vector(local.x, 0, local.z)));
}

/*
t_vector compute_cylinder_normal(t_cylinder *cy, t_vector point)
{
    // Compute vector from cylinder center to the point.
    t_vector v = subtract(point, cy->center);

    // Projection of v along the cylinder's axis.
    double dist = dot(v, cy->axis);

    // Determine the half height of the cylinder.
    double half_height = cy->height / 2.0;

    // If the cylinder is closed and the point is on a cap, return the cap normal.
    if (cy->closed) {
         if (fabs(dist - half_height) < EPSILON)
             return cy->axis;  // Top cap
         else if (fabs(dist + half_height) < EPSILON)
             return multiplication(cy->axis, -1);  // Bottom cap
    }

    // Otherwise, compute the lateral surface normal.
    t_vector lateral = subtract(v, multiplication(cy->axis, dist));
    return normalization(lateral);
}
*/

/*please rename this function */
t_vector v2normal_at(t_object obj, t_vector point, t_ray r)
{
	t_sphere	*sphere;
	t_plane		*plane;
	t_cylinder	*cylinder;

	if (obj.type == T_SPHERE)
	{
		sphere = (t_sphere *)obj.address;
		return (normalization(subtract(point, sphere->center)));
	}
	if (obj.type == T_PLANE)
	{
		plane = (t_plane *)obj.address;
		return (get_plane_normal(plane, r));
	}
	if (obj.type == T_CYLINDER)
	{
		cylinder = (t_cylinder *)obj.address;
		return (default_cylinder_normal(cylinder, point));
	}
	printf("v2normal failure: obj TYPE not found\n");
	exit(-42);
}

t_vector	reflect(t_vector in, t_vector normal)
{
	return (subtract(in, multiplication(normal, 2 * dot(in, normal))));
}

// You may assume that the point will always be on the surface of the sphere
// TODO: leaks
t_vector	normal_at(t_sphere sphere, t_vector world_point)
{
	t_vector	object_point;
	t_vector	object_normal;
	t_vector	world_normal;
	t_vector	point;

	object_point = matrix_x_vector(inversing_matrix(4, sphere.transform) , world_point);
	point = create_point(0, 0, 0);
	object_normal = subtract(object_point, point);
	world_normal = matrix_x_vector(transposing(4, 4, inversing_matrix(4, sphere.transform)), object_normal);
	world_normal.w = 0;
	return (normalization(world_normal));
}
