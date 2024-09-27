/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersection_plane.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atucci <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/03 15:26:02 by atucci            #+#    #+#             */
/*   Updated: 2024/09/27 16:09:02 by atucci           ###   ########.fr       */
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

	list = NULL;
	ray = transform_ray(old_ray, inversing_matrix(4, plane.transform));
	denominator = dot(plane.normal, ray.direction);
	if (fabs(denominator) < EPSILON_v2)
		return (printf("returning null\n"), NULL);
	t = dot(subtract(plane.point, ray.origin), plane.normal) / denominator;
	if (t < 0)
		return (printf("returning null\n"),NULL);
	inter = intersection(t, plane.identifier, &plane);
	add_intersection_l(&list, &inter);
	return (list);
}
