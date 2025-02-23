/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersection_sphere.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftroise <ftroise@student.42roma.it>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/14 10:04:11 by atucci            #+#    #+#             */
/*   Updated: 2025/02/23 18:51:36 by atucci           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

static t_ray	create_sphere_ray(t_sphere *sphere, t_ray old_ray)
{
	double	**leaking_matrix;
	double	**cp;
	t_ray	ray;

	cp = copy_matrix(4, 4, sphere->transform);
	leaking_matrix = inversing_matrix(4, cp);
	ray = transform_ray(old_ray, leaking_matrix);
	free_heap_matrix(leaking_matrix, 4);
	free_heap_matrix(cp, 4);
	return (ray);
}

static void	calculate_t_values(double *t, t_vector sph_ray, t_ray ray, double r)
{
	double	discriminant;
	double	a;
	double	b;

	a = dot(ray.direction, ray.direction);
	b = -2.0 * dot(sph_ray, ray.direction);
	discriminant = get_discriminant(sph_ray, ray, r);
	t[0] = (b - sqrt(discriminant)) / (2.0 * a);
	t[1] = (b + sqrt(discriminant)) / (2.0 * a);
}

static void	handle_intersections(t_list_intersect **lis, double *t, t_sphere *s)
{
	t_intersection	inter1;
	t_intersection	inter2;

	inter1 = intersection(t[0], s->identifier, s);
	inter2 = intersection(t[1], s->identifier, s);
	add_intersection_l(lis, &inter1);
	if (!comparing_double(t[0], t[1]))
		add_intersection_l(lis, &inter2);
}

t_list_intersect	*intersect_sphere(t_sphere *sphere, t_ray old_ray)
{
	t_vector			sphere_to_ray;
	double				t[2];
	t_list_intersect	*list;
	t_ray				ray;

	list = NULL;
	ray = create_sphere_ray(sphere, old_ray);
	sphere_to_ray = get_sphere_to_ray(*sphere, ray);
	if (get_discriminant(sphere_to_ray, ray, sphere->diameter / 2.0) < 0)
		return (NULL);
	calculate_t_values(t, sphere_to_ray, ray, sphere->diameter / 2.0);
	handle_intersections(&list, t, sphere);
	return (list);
}
