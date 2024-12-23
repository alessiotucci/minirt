/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersection_plane.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atucci <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/03 15:26:02 by atucci            #+#    #+#             */
/*   Updated: 2024/12/23 16:41:05 by atucci           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

t_list_intersect	*intersect_plane(t_plane plane, t_ray old_ray)
{
	t_ray				ray;
	t_list_intersect	*list;
	t_intersection		inter;
	double				t;
	double				denominator;
	//TODO: LEAK MATRIX
	double **leaking_matrix;
	double **cp;
	
	cp = copy_matrix(4, 4, plane.transform);
	//leaking_matrix = inversing_matrix(4, copy_matrix(4, 4, plane.transform));
	leaking_matrix = inversing_matrix(4, cp);

	list = NULL;
	ray = transform_ray(old_ray, leaking_matrix);
	free_heap_matrix(leaking_matrix, 4);
	free_heap_matrix(cp, 4);
	denominator = dot(plane.normal, ray.direction);
	if (fabs(denominator) < EPSILON_v2)
		return (/*printf("PLANE: returning null\n"),*/ NULL);
	t = dot(subtract(plane.point, ray.origin), plane.normal) / denominator;
	if (t < 0)
		return (/*printf("PLANE: returning null\n"),*/ NULL);
	inter = intersection(t, plane.identifier, &plane);
	add_intersection_l(&list, &inter);
	return (list);
}
