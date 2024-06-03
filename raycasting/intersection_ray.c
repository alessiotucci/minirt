/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersection_ray.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atucci <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 16:54:27 by atucci            #+#    #+#             */
/*   Updated: 2024/06/03 14:01:25 by atucci           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

/* The vector from the sphere's center, to the ray origin */
t_vector	get_sphere_to_ray(t_sphere sphere, t_ray ray)
{
	return (subtract(ray.origin, sphere.center));
}

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

t_intersection	intersect_sphere(t_sphere sphere, t_ray ray)
{
	t_intersection	intersection;
	t_vector		sphere_to_ray;
	double			discriminant;
	double			t[2];

	sphere_to_ray = get_sphere_to_ray(sphere, ray);
	discriminant = get_discriminant(sphere_to_ray, ray, sphere.diameter);//TODO:
	if (discriminant < 0)
		intersection.count = 0;
	else
	{
		t[0] = (-2.0 * dot(sphere_to_ray, ray.direction) - sqrt(discriminant)) / (2.0 * dot(ray.direction, ray.direction));
		t[1] = (-2.0 * dot(sphere_to_ray, ray.direction) + sqrt(discriminant)) / (2.0 * dot(ray.direction, ray.direction));
		intersection.t[0] = t[0];//add(ray.origin, multiplication(ray.direction, t[0]));
		intersection.t[1] = t[1];//add(ray.origin, multiplication(ray.direction, t[1]));
		//intersection.count = (t[0] == t[1]) ? 1 : 2;
		if (comparing_double(t[0], t[1]))
			intersection.count = 1;
		else
			intersection.count = 2;
	}
	return (intersection);
}

void	print_intersection(t_intersection i, t_sphere s)
{
	printf("intersection (%s%d%s) with the sphere [%s]\n", RED, i.count, RESET, s.identifier);
	if (i.count != 0)
	{
		printf("values[0]%f\n", i.t[0]);
		printf("values[1]%f\n", i.t[1]);
	}
}
/* Main to test out the function */
int	main()
{
	printf("\nTEST 1\n");
	t_color bogus;
	bogus.r = 0; bogus.g = 0; bogus.b = 0;
	t_vector p = create_point(0, 0, 0);
	t_sphere a = create_sphere("a", p, 1.0, bogus); // create unit sphere

	t_vector origin = create_point(0, 0, -5);
	t_vector direction = create_vector(0, 0, 1);
	t_ray ray = create_ray(origin, direction); // created a ray here
	t_intersection test = intersect_sphere(a, ray);
	print_intersection(test, a);

	printf("\n\nTEST 2\n");
	t_vector origin1 = create_point(0, 1, -5);
	t_vector direction1 = create_vector(0, 0, 1);
	t_ray ray1 = create_ray(origin1, direction1); // created a ray here
	t_intersection test1 = intersect_sphere(a, ray1);
	print_intersection(test1, a);

	printf("\n\nTEST 3\n");
	t_vector origin2 = create_point(0, 2, -5);
	t_vector direction2 = create_vector(0, 0, 1);
	t_ray ray2 = create_ray(origin2, direction2); // created a ray here
	t_intersection test2 = intersect_sphere(a, ray2);
	print_intersection(test2, a);

	printf("\n\nTEST 4\n");
	t_vector origin3 = create_point(0, 0, 0);
	t_vector direction3 = create_vector(0, 0, 1);
	t_ray ray3 = create_ray(origin3, direction3); // created a ray here
	t_intersection test3 = intersect_sphere(a, ray3);
	print_intersection(test3, a);

	printf("\n\nTEST 5\n");
	t_vector origin4 = create_point(0, 0, 5);
	t_vector direction4 = create_vector(0, 0, 1);
	t_ray ray4 = create_ray(origin4, direction4); // created a ray here
	t_intersection test4 = intersect_sphere(a, ray4);
	print_intersection(test4, a);

}

// gcc ../matrix/*.c ../vector/*.c create_ray.c intersection_ray.c  ../extra/comparing.c ../extra/print_debug.c ../shapes/sphere.c  ../libft/libft.a -lm
