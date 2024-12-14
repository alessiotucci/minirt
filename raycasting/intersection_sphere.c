/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersection_sphere.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atucci <atucci@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/14 10:01:50 by atucci            #+#    #+#             */
/*   Updated: 2024/12/14 10:02:18 by atucci           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../minirt.h"

//TODO: rename this function
t_list_intersect *intersect_sphereV2(t_sphere sphere, t_ray old_ray)
{
	t_vector sphere_to_ray;
	double discriminant;
	double t[2];
	t_list_intersect *list = NULL;
	t_intersection inter1;
	t_intersection inter2;
	t_ray ray;

	ray = transform_ray(old_ray, inversing_matrix(4, copy_matrix(4, 4, sphere.transform)));
	sphere_to_ray = get_sphere_to_ray(sphere, ray);
	discriminant = get_discriminant(sphere_to_ray, ray, sphere.diameter / 2.0); // diameter/2 for radius
	if (discriminant < 0)
	{
		// No intersections, return an empty list
		return (NULL);
	}
	t[0] = (-2.0 * dot(sphere_to_ray, ray.direction) - sqrt(discriminant)) / (2.0 * dot(ray.direction, ray.direction));
	t[1] = (-2.0 * dot(sphere_to_ray, ray.direction) + sqrt(discriminant)) / (2.0 * dot(ray.direction, ray.direction));

	inter1 = intersection(t[0], sphere.identifier, &sphere);
	inter2 = intersection(t[1], sphere.identifier, &sphere);
	if (comparing_double(t[0], t[1]))
	{
		add_intersection_l(&list, &inter1);
		return list;
	}
	else
	{
		add_intersection_l(&list, &inter1);
		add_intersection_l(&list, &inter2);
		return list;
	}
}

