/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersection_plane.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftroise <ftroise@student.42roma.it>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/03 15:26:02 by atucci            #+#    #+#             */
/*   Updated: 2025/02/23 18:02:27 by atucci           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

static t_ray	create_plane_ray(t_plane *plane, t_ray old_ray)
{
	double				**leaking_matrix;
	double				**cp;
	t_ray				ray;

	cp = copy_matrix(4, 4, plane->transform);
	leaking_matrix = inversing_matrix(4, cp);
	ray = transform_ray(old_ray, leaking_matrix);
	free_heap_matrix(leaking_matrix, 4);
	free_heap_matrix(cp, 4);
	return (ray);
}

t_list_intersect	*intersect_plane(t_plane *plane, t_ray old_ray)
{
	t_ray				ray;
	t_list_intersect	*list;
	t_intersection		inter;
	double				t;
	double				denominator;

	list = NULL;
	ray = create_plane_ray(plane, old_ray);
	denominator = dot(plane->normal, ray.direction);
	if (fabs(denominator) < EPSILON_V2)
		return (NULL);
	t = dot(subtract(plane->point, ray.origin), plane->normal) / denominator;
	if (t < 0)
		return (NULL);
	inter = intersection(t, plane->identifier, plane);
	add_intersection_l(&list, &inter);
	return (list);
}
