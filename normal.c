/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   normal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atucci <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 14:24:11 by atucci            #+#    #+#             */
/*   Updated: 2025/02/24 17:27:33 by atucci           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

//REASON  gpt
// Get the stored normal.
// If the dot product between the ray's direction and the normal is positive,
// then the ray is coming from behind the plane.
// Flip the normal so that it faces the ray.
// 1
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
// 2
t_vector	local_point_in_cylinder(t_cylinder *cylinder, t_vector point)
{
	t_vector	local;

	local.x = point.x - cylinder->center.x;
	local.y = point.y;
	local.z = point.z - cylinder->center.z;
	local.w = point.w;
	return (local);
}

/* for the cylinder */
// 3
t_vector	compute_cylinder_normal(t_cylinder *cy, t_vector point)
{
	double		dist;
	double		half_height;
	t_vector	v;
	t_vector	lateral;

	v = subtract(point, cy->center);
	dist = dot(v, cy->axis);
	half_height = cy->height / 2.0;
	if (cy->closed)
	{
		if (fabs(dist - half_height) < EPSILON)
			return (cy->axis);
		else if (fabs(dist + half_height) < EPSILON)
			return (multiplication(cy->axis, -1));
	}
	lateral = subtract(v, multiplication(cy->axis, dist));
	return (normalization(lateral));
}

/*please rename this function */
// 4
t_vector	v2normal_at(t_object obj, t_vector point, t_ray r)
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
		return (compute_cylinder_normal(cylinder, point));
	}
	printf("v2normal failure: obj TYPE not found\n");
	exit(-42);
}

//5 
t_vector	reflect(t_vector in, t_vector normal)
{
	return (subtract(in, multiplication(normal, 2 * dot(in, normal))));
}
