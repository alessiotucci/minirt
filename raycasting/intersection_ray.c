/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersection_ray.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftroise <ftroise@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 16:54:27 by atucci            #+#    #+#             */
/*   Updated: 2024/07/25 12:45:11 by atucci           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

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

/* this function create the intersection, need to be updated */
t_intersection	intersect_sphere(t_sphere sphere, t_ray ray)
{
	t_intersection	inter;
	t_vector		sphere_to_ray;
	double			discriminant;
	double			t[2];

	sphere_to_ray = get_sphere_to_ray(sphere, ray);
	discriminant = get_discriminant(sphere_to_ray, ray, sphere.diameter);//TODO:
	if (discriminant < 0)
		inter.count = 0;
	else
	{
		t[0] = (-2.0 * dot(sphere_to_ray, ray.direction) - sqrt(discriminant)) / (2.0 * dot(ray.direction, ray.direction));
		t[1] = (-2.0 * dot(sphere_to_ray, ray.direction) + sqrt(discriminant)) / (2.0 * dot(ray.direction, ray.direction));
		inter.t[0] = t[0];//add(ray.origin, multiplication(ray.direction, t[0]));
		inter.t[1] = t[1];//add(ray.origin, multiplication(ray.direction, t[1]));
		if (comparing_double(t[0], t[1]))
			inter.count = 1;
		else
			inter.count = 2;
	}
	//TODO: Create an helper function to  Update the obj field in the structure
	inter.obj.type = T_SPHERE;
	inter.obj.obj = &sphere;
	return (inter);
}
/*TODO: UPDATED version, need to be tested as well to check if it's working
t_intersection_list *new_intersect_sphere(t_sphere sphere, t_ray ray)
{
	t_vector	sphere_to_ray;
	t_intersection_list	*list;
	double	t0;
	double	t1;
	double	discriminant;
	t_intersection	inter1;
	t_intersection	inter2;

	sphere_to_ray = get_sphere_to_ray(sphere, ray);
	discriminant = get_discriminant(sphere_to_ray, ray, sphere.diameter);
	if (discriminant < 0)
	{
		list = create_intersection_list(0);
		return (list);
	}
	list = create_intersection_list(2);
	if (!list)
	{
		printf("Memory allocation for the list failed\n");
		return (NULL);
	}
	t0 = (-2.0 * dot(sphere_to_ray, ray.direction) - sqrt(discriminant)) / (2.0 * dot(ray.direction, ray.direction));
	t1 = (-2.0 * dot(sphere_to_ray, ray.direction) + sqrt(discriminant)) / (2.0 * dot(ray.direction, ray.direction));
	inter1 = create_intersection(t0, &sphere);
	inter2 = create_intersection(t1, &sphere);
	if (comparing_double(t0, t1))
	{
		list->count = 1;
		add_intersection(list, 0, inter1);
	}
	else
	{
		list->count = 2;
		add_intersection(list, 0, inter1);
		add_intersection(list, 1, inter2);
	}
	return (list);
}
*/
/* Main to test out the function
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
	print_intersection(test);//, a);

	printf("\n\nTEST 2\n");
	t_vector origin1 = create_point(0, 1, -5);
	t_vector direction1 = create_vector(0, 0, 1);
	t_ray ray1 = create_ray(origin1, direction1); // created a ray here
	t_intersection test1 = intersect_sphere(a, ray1);
	print_intersection(test1);//, a);

	printf("\n\nTEST 3\n");
	t_vector origin2 = create_point(0, 2, -5);
	t_vector direction2 = create_vector(0, 0, 1);
	t_ray ray2 = create_ray(origin2, direction2); // created a ray here
	t_intersection test2 = intersect_sphere(a, ray2);
	print_intersection(test2);//, a);

	printf("\n\nTEST 4\n");
	t_vector origin3 = create_point(0, 0, 0);
	t_vector direction3 = create_vector(0, 0, 1);
	t_ray ray3 = create_ray(origin3, direction3); // created a ray here
	t_intersection test3 = intersect_sphere(a, ray3);
	print_intersection(test3);//, a);

	printf("\n\nTEST 5\n");
	t_vector origin4 = create_point(0, 0, 5);
	t_vector direction4 = create_vector(0, 0, 1);
	t_ray ray4 = create_ray(origin4, direction4); // created a ray here
	t_intersection test4 = intersect_sphere(a, ray4);
	print_intersection(test4);//, a);

}
*/
 
// gcc ../matrix/*.c ../vector/*.c create_ray.c intersection_ray.c  ../extra/comparing.c ../extra/print_debug.c ../shapes/sphere.c  ../libft/libft.a -lm
