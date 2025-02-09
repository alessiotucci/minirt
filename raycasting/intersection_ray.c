/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersection_ray.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftroise <ftroise@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 16:54:27 by atucci            #+#    #+#             */
/*   Updated: 2025/02/09 20:11:46 by atucci           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

//typedef struct s_intersection_list
//{
//	t_intersection	*intersections;
//	int count;
//}	t_intersection_list;

/* The vector from the sphere's center, to the ray origin */
t_vector	get_sphere_to_ray(t_sphere sphere, t_ray ray)
{
	return (subtract(ray.origin, sphere.center));
}

/* function to get the discriminant */
double	get_discriminant(t_vector sphere_to_ray, t_ray ray, double diameter)
{
	double	a;
	double	b;
	double	c;

	a = dot(ray.direction, ray.direction);
	b = 2.0 * dot(ray.direction, sphere_to_ray);
	c = dot(sphere_to_ray, sphere_to_ray) - diameter * diameter ;
	return ((b * b) - 4 * a * c);
}

/* Main to test out the function */
/*
int	main()
{
	printf("\nTEST 1\n");
	t_color bogus;
	bogus.r = 0; bogus.g = 0; bogus.b = 0;
	t_vector p = create_point(0, 0, 0);
	t_sphere a = create_sphere("sp", p, 1.0, bogus); // create unit sphere

	t_vector origin = create_point(0, 0, -5);
	t_vector direction = create_vector(0, 0, 1);
	t_ray ray = create_ray(origin, direction); // created a ray here
	t_intersection_list *test = intersect_sphere(a, ray);
	print_intersection_list(test);
	free_intersection_list(test);

	printf("\n\nTEST 2\n");
	t_vector origin1 = create_point(0, 1, -5);
	t_vector direction1 = create_vector(0, 0, 1);
	t_ray ray1 = create_ray(origin1, direction1); // created a ray here
	t_intersection_list *test1 = intersect_sphere(a, ray1);
	print_intersection_list(test1);
	free_intersection_list(test1);

	printf("\n\nTEST 3\n");
	t_vector origin2 = create_point(0, 2, -5);
	t_vector direction2 = create_vector(0, 0, 1);
	t_ray ray2 = create_ray(origin2, direction2); // created a ray here
	t_intersection_list *test2 = intersect_sphere(a, ray2);
	print_intersection_list(test2);
	free_intersection_list(test2);

	printf("\n\nTEST 4\n");
	t_vector origin3 = create_point(0, 0, 0);
	t_vector direction3 = create_vector(0, 0, 1);
	t_ray ray3 = create_ray(origin3, direction3); // created a ray here
	t_intersection_list *test3 = intersect_sphere(a, ray3);
	print_intersection_list(test3);
	free_intersection_list(test3);

	printf("\n\nTEST 5\n");
	t_vector origin4 = create_point(0, 0, 5);
	t_vector direction4 = create_vector(0, 0, 1);
	t_ray ray4 = create_ray(origin4, direction4); // created a ray here
	t_intersection_list *test4 = intersect_sphere(a, ray4);
	print_intersection_list(test4);
	free_intersection_list(test4);
}
*/ 
// gcc ../matrix/*.c ../vector/*.c create_ray.c intersection_ray.c  ../extra/comparing.c ../extra/print_debug.c ../shapes/sphere.c  ../libft/libft.a -lm
