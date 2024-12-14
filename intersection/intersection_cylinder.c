/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersection_cylinder.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atucci <atucci@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 13:27:39 by atucci            #+#    #+#             */
/*   Updated: 2024/12/14 11:24:31 by atucci           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"


/* return a list of intersection like usual */
t_list_intersect	*intersect_cylinder(t_cylinder cylinder, t_ray old_ray)
{
	double	a;
	double	b;
	double	c;
	double	disc;
	t_list_intersect *list = NULL;
	t_intersection inter1;
	t_intersection inter2;(void)inter2;
	t_ray ray; (void)ray;

	a = (pow(old_ray.direction.x, 2) + pow(old_ray.direction.z, 2));
	if (comparing_double(a, 0.0))
		return (NULL);
	b = (2 * old_ray.origin.x * old_ray.direction.x) + (2 * old_ray.origin.z * old_ray.direction.z);
	c = (pow(old_ray.origin.x, 2) + pow(old_ray.origin.z, 2) - 1);
	disc = pow(b, 2) - 4 * a * c;
	if (disc < 0)
		return (NULL);
	else
	{
		printf("else, core dump ofc\n");exit(0);
		double fake = 1;//PLACEHOLDER FUNCTION
		inter1 = intersection(fake, cylinder.identifier, &cylinder);
		add_intersection_l(&list, &inter1);
		return (list);
	}
}



// Function to test the intersection of a ray with a cylinder
int main()
{
	printf("%sTEST:%s intersect_cylinder function\n", RED, RESET);

	// Create a unit cylinder
	t_color bogus;
	bogus.r = 0; bogus.g = 0; bogus.b = 0;
	t_vector center = create_point(0, 0, 0);
	t_cylinder cyl = create_cylinder("Cyl", center, 1.0, bogus);

	// Create rays that should miss the cylinder
	t_vector origin1 = create_point(1, 0, 0);
	t_vector direction1 = create_vector(0, 1, 0);
	t_ray ray1 = create_ray(origin1, direction1);

	t_vector origin2 = create_point(0, 0, 0);
	t_vector direction2 = create_vector(0, 1, 0);
	t_ray ray2 = create_ray(origin2, direction2);

	t_vector origin3 = create_point(0, 0, -5);
	t_vector direction3 = create_vector(1, 1, 1);
	t_ray ray3 = create_ray(origin3, direction3);

	// Test the intersection function
	t_list_intersect *intersections1 = intersect_cylinder(cyl, ray1);
	t_list_intersect *intersections2 = intersect_cylinder(cyl, ray2);
	t_list_intersect *intersections3 = intersect_cylinder(cyl, ray3);

	// Verify that the function returns no intersections
	if (intersections1 == NULL && intersections2 == NULL && intersections3 == NULL)
		printf("%sTEST PASSED:%s All rays miss the cylinder\n", GREEN, RESET);
	else
		printf("%sTEST FAILED:%s Some rays intersected the cylinder\n", RED, RESET);
	return 0;
}

