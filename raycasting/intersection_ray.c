/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersection_ray.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atucci <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 16:54:27 by atucci            #+#    #+#             */
/*   Updated: 2024/06/02 18:21:08 by atucci           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

double	*intersect_sphere(t_sphere sphere, t_ray ray)
{

}


/* Main to test out the function */
int	main()
{
	t_color bogus;
	bogus.r = 0; bogus.g = 0; bogus.b = 0;
	t_vector p = create_point(0, 0, 0);
	t_sphere a = create_sphere("a", p, 1.0, bogus); // create unit sphere

	t_vector origin = create_point(0, 0, -5);
	t_vector direction = create_vector(0, 0, 1);
	t_ray ray = create_ray(origin, direction); // created a ray here
	intersect_sphere(a, ray);
}


/*
 *
 *
	typedef struct s_intersection
{
	int		count;
	t_vector	point[2];
}	t_intersection;

 *t_vector	get_oc(t_sphere sphere, t_ray ray)
{
	return (subtract(ray.origin, sphere.center));
}

double	get_discriminant(t_vector oc, t_ray ray, double diameter)
{
	double	a;
	double	b;
	double	c;

	a = dot_product(ray.direction, ray.direction);
	b = 2.0 * dot_product(oc, ray.direction);
	c = dot_product(oc, oc) - diameter * diameter / 4.0;
	return (b * b - 4 * a * c);
}

t_intersection	*intersect_sphere(t_sphere sphere, t_ray ray)
{
	t_intersection	*intersection;
	t_vector	oc;
	double		discriminant;
	double		t[2];

	intersection = (t_intersection *)malloc(sizeof(t_intersection));
	if (!intersection)
		return (NULL);
	oc = get_oc(sphere, ray);
	discriminant = get_discriminant(oc, ray, sphere.diameter);
	if (discriminant < 0)
	{
		intersection->count = 0;
	}
	else
	{
		t[0] = (-2.0 * dot_product(oc, ray.direction) - sqrt(discriminant)) / (2.0 * dot_product(ray.direction, ray.direction));
		t[1] = (-2.0 * dot_product(oc, ray.direction) + sqrt(discriminant)) / (2.0 * dot_product(ray.direction, ray.direction));
		intersection->point[0] = add(ray.origin, multiply(ray.direction, t[0]));
		intersection->point[1] = add(ray.origin, multiply(ray.direction, t[1]));
		intersection->count = (t[0] == t[1]) ? 1 : 2;
	}
	return (intersection);
}

 * */
