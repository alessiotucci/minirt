/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_shadowed.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atucci <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/29 12:55:10 by atucci            #+#    #+#             */
/*   Updated: 2025/02/23 19:06:10 by atucci           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

/* Check if a point is in a shadows */
/* Step 1: Get the vector to the light source and calculate distance */
/* Step 2: Create the shadow ray in the direction of the light */
/* Step 3: Intersect the world with the shadow ray */
/* Step 4: Check for the closest hit */
//TODO: important function useful for refactoring

static void	loop_over_spheres(t_setting *world, t_ray ray,
				t_list_intersect **all_intersections)
{
	int					i;
	t_list_intersect	*current_intersections;

	i = 0;
	while (i < world->num_spheres)
	{
		current_intersections = intersect_sphere(world->spheres[i], ray);
		if (current_intersections)
			concatenate_lists(all_intersections, current_intersections);
		i++;
	}
}

static void	loop_over_planes(t_setting *world, t_ray ray,
				t_list_intersect **all_intersections)
{
	int					i;
	t_list_intersect	*current_intersections;

	i = 0;
	while (i < world->num_planes)
	{
		current_intersections = intersect_plane(world->planes[i], ray);
		if (current_intersections)
			concatenate_lists(all_intersections, current_intersections);
		i++;
	}
}

static void	loop_over_cylinders(t_setting *world, t_ray ray,
				t_list_intersect **all_intersections)
{
	int					i;
	t_list_intersect	*current_intersections;

	i = 0;
	while (i < world->num_cylinders)
	{
		current_intersections = intersect_cylinder(world->cylinders[i], ray);
		if (current_intersections)
			concatenate_lists(all_intersections, current_intersections);
		i++;
	}
}

t_list_intersect	*intersect_world(t_setting *world, t_ray ray)
{
	t_list_intersect	*all_intersections;

	all_intersections = NULL;
	loop_over_spheres(world, ray, &all_intersections);
	loop_over_planes(world, ray, &all_intersections);
	loop_over_cylinders(world, ray, &all_intersections);
	sort_intersection_list(&all_intersections);
	return (all_intersections);
}

int	is_shadowed(t_setting *world, t_vector point, t_light light)
{
	t_vector			v;
	double				distance;
	t_ray				shadow_ray;
	t_list_intersect	*intersections;
	t_intersection		*closest_hit;

	v = subtract(light.position, point);
	distance = magnitude(v);
	shadow_ray.origin = point;
	shadow_ray.direction = normalization(v);
	intersections = intersect_world(world, shadow_ray);
	closest_hit = hit_v2(intersections);
	if (closest_hit != NULL && closest_hit->t < distance)
		return (free_list(&intersections), 1);
	return (free_list(&intersections), 0);
}
