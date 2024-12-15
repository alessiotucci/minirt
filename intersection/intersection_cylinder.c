/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersection_cylinder.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atucci <atucci@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 13:27:39 by atucci            #+#    #+#             */
/*   Updated: 2024/12/15 19:10:38 by atucci           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

int	check_cap_cylinder(t_ray ray, double t)
{
	double	x;
	double	z;

	x = ray.origin.x + t * ray.direction.x;
	z = ray.origin.z + t * ray.direction.z;
	return (pow(x, 2) + (pow(z, 2)) <= 1);
}

// Function to intersect with the caps of the cylinder
static void intersect_caps(t_cylinder cylinder, t_ray ray, t_list_intersect **list)
{
	double		t;
	t_intersection	inter1;
	t_intersection	inter2;

	// Caps only matter if the cylinder is closed and might possibly be intersected by the ray
	if (!cylinder.closed || comparing_double(ray.direction.y, 0.0))
		return ;
	t = (cylinder.min - ray.origin.y) / ray.direction.y;
	if (check_cap_cylinder(ray, t))
	{
		inter1 = intersection(t, cylinder.identifier, &cylinder);
		add_intersection_l(list, &inter1);
	}
	t = (cylinder.max - ray.origin.y) / ray.direction.y;
	if (check_cap_cylinder(ray, t))
	{
		inter2 = intersection(t, cylinder.identifier, &cylinder);
		add_intersection_l(list, &inter2);
	}
}


static t_list_intersect	*intersection_happened(double t[2], t_intersection inter1, t_intersection inter2, t_ray old_ray, t_cylinder cylinder)
{
	double	temp;
	double	y0;
	double	y1;
	t_list_intersect *list;

	list = NULL;
	//TODO create a swap function if needed
	if (t[0] > t[1])
	{
		temp = t[0];
		t[0] = t[1];
		t[1] = temp;
	}
    // Check if the intersection points are within the cylinder's bounds
	y0 = old_ray.origin.y + t[0] * old_ray.direction.y;
	y1 = old_ray.origin.y + t[1] * old_ray.direction.y;
	if (cylinder.min < y0 && y0 < cylinder.max)
	{
		inter1 = intersection(t[0], cylinder.identifier, &cylinder);
		add_intersection_l(&list, &inter1);
	}
	if (cylinder.min < y1 && y1 < cylinder.max)
	{
		inter2 = intersection(t[1], cylinder.identifier, &cylinder);
		add_intersection_l(&list, &inter2);
	}
	return (list);
}

/* return a list of intersection like usual */
t_list_intersect	*intersect_cylinder(t_cylinder cylinder, t_ray old_ray)
{
	double	a;
	double	b;
	double	c;
	double	disc;
	double	t[2];
	t_list_intersect *list = NULL;
	t_intersection inter1;
	t_intersection inter2;
	//t_ray ray;

	a = (pow(old_ray.direction.x, 2) + pow(old_ray.direction.z, 2));
	if (comparing_double(a, 0.0))
	{
		printf("CYLINDER: returning null\n");
		return (NULL);
	}
	b = (2 * old_ray.origin.x * old_ray.direction.x) + (2 * old_ray.origin.z * old_ray.direction.z);
	c = (pow(old_ray.origin.x, 2) + pow(old_ray.origin.z, 2) - 1);
	//printf("pow(b, 2)) = [%lf] - (4 * a * c) = [%lf]\n", pow(b, 2), 4 * a * c);
	disc = (pow(b, 2)) - (4 * a * c);
	//disc = ((b * b) - (4 * a * c));
	if (disc < 0)
	{
		printf("CYLINDER: returning null\n");
		return (NULL);
	}
	else
	{
		//printf("DEBUG: a[%lf]\tb[%lf]\tc[%lf]\tdisc[%lf]\n", a, b, c, disc);
		t[0] = ((-b - sqrt(disc)) / (2 * a));
		t[1] = ((-b + sqrt(disc)) / (2 * a));
		list = intersection_happened(t, inter1, inter2, old_ray, cylinder);

		/*
		inter1 = intersection(t[0], cylinder.identifier, &cylinder);
		inter2 = intersection(t[1], cylinder.identifier, &cylinder);
		add_intersection_l(&list, &inter1);
		add_intersection_l(&list, &inter2);
		return (list);
		*/
	}
	intersect_caps(cylinder, old_ray, &list);
	return (list);
}



/* Function to test the intersection of a ray with a cylinder
int main()
{
	printf("%sTEST:%s intersect_cylinder function\n", RED, RESET);

	// Create a unit cylinder
	t_color bogus;
	bogus.r = 0; bogus.g = 0; bogus.b = 0;
	t_vector center = create_point(0, 0, 0);
	t_cylinder cyl = create_cylinder("cy", center, 1.0, bogus);

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

	// Create rays that should intersect the cylinder
    t_vector origin4 = create_point(1, 0, -5);
    t_vector direction4 = create_vector(0, 0, 1);
    t_ray ray4 = create_ray(origin4, direction4);

    t_vector origin5 = create_point(0, 0, -5);
    t_vector direction5 = create_vector(0, 0, 1);
    t_ray ray5 = create_ray(origin5, direction5);

    t_vector origin6 = create_point(0.5, 0, -5);
    t_vector direction6 = create_vector(0.1, 1, 1);
    t_ray ray6 = create_ray(origin6, direction6);

    // Test the intersection function
    t_list_intersect *intersections4 = intersect_cylinder(cyl, ray4);
    t_list_intersect *intersections5 = intersect_cylinder(cyl, ray5);
    t_list_intersect *intersections6 = intersect_cylinder(cyl, ray6);

    // Print the intersection lists
    printf("Intersections for ray4:\n\n");
    print_list(&intersections4);
	free_list(&intersections4);
    printf("Intersections for ray5:\n\n");
    print_list(&intersections5);
	free_list(&intersections5);
    printf("Intersections for ray6:\n\n");
    print_list(&intersections6);
	free_list(&intersections6);
	return 0;
}

*/
/*
int main()
{
	printf("%sTEST:%s truncated cylinder function\n", RED, RESET);

	// Create a unit cylinder
	t_color bogus;
	bogus.r = 0; bogus.g = 0; bogus.b = 0;
	t_vector center = create_point(0, 0, 0);
	t_cylinder cyl = create_cylinder("cy", center, 1.0, bogus);
	// Update min and max values
	set_cylinder_size(&cyl, 1, 2);

	// Create rays to test the truncated cylinder
	t_vector origin1 = create_point(0, 1.5, 0);
	t_vector direction1 = create_vector(0.1, 1, 0);
	t_ray ray1 = create_ray(origin1, direction1);

	t_vector origin2 = create_point(0, 3, -5);
	t_vector direction2 = create_vector(0, 0, 1);
	t_ray ray2 = create_ray(origin2, direction2);

	t_vector origin3 = create_point(0, 0, -5);
	t_vector direction3 = create_vector(0, 0, 1);
	t_ray ray3 = create_ray(origin3, direction3);

	t_vector origin4 = create_point(0, 2, -5);
	t_vector direction4 = create_vector(0, 0, 1);
	t_ray ray4 = create_ray(origin4, direction4);

	t_vector origin5 = create_point(0, 1, -5);
	t_vector direction5 = create_vector(0, 0, 1);
	t_ray ray5 = create_ray(origin5, direction5);

	t_vector origin6 = create_point(0, 1.5, -2);
	t_vector direction6 = create_vector(0, 0, 1);
	t_ray ray6 = create_ray(origin6, direction6);

	// Test the intersection function
	t_list_intersect *intersections1 = intersect_cylinder(cyl, ray1);
	t_list_intersect *intersections2 = intersect_cylinder(cyl, ray2);
	t_list_intersect *intersections3 = intersect_cylinder(cyl, ray3);
	t_list_intersect *intersections4 = intersect_cylinder(cyl, ray4);
	t_list_intersect *intersections5 = intersect_cylinder(cyl, ray5);
	t_list_intersect *intersections6 = intersect_cylinder(cyl, ray6);

	printf("Intersections for ray1:\n\n");
	print_list(&intersections1);
	free_list(&intersections1);
	printf("Intersections for ray2:\n\n");
	print_list(&intersections2);
	free_list(&intersections2);
	printf("Intersections for ray3:\n\n");
	print_list(&intersections3);
	free_list(&intersections3);

	// Print the intersection lists
	printf("Intersections for ray4:\n\n");
	print_list(&intersections4);
	free_list(&intersections4);
	printf("Intersections for ray5:\n\n");
	print_list(&intersections5);
	free_list(&intersections5);
	printf("Intersections for ray6:\n\n");
	print_list(&intersections6);
	free_list(&intersections6);
	return 0;
}
*/

/*
int main()
{
	printf("%sTEST:%s capped cylinder function\n", RED, RESET);

	// Create a unit cylinder
	t_color bogus;
	bogus.r = 0; bogus.g = 0; bogus.b = 0;
	t_vector center = create_point(0, 0, 0);
	t_cylinder cyl = create_cylinder("cy", center, 1.0, bogus);
	// Update min and max values
	set_cylinder_size(&cyl, 1, 2);
	set_cylinder_cap(&cyl);

	// Create rays to test the truncated cylinder
	t_vector origin1 = create_point(0, 3, 0);
	t_vector direction1 = create_vector(0, -1, 0);
	t_ray ray1 = create_ray(origin1, direction1);

	t_vector origin2 = create_point(0, 3, -2);
	t_vector direction2 = create_vector(0, -1, 2);
	t_ray ray2 = create_ray(origin2, direction2);

	t_vector origin3 = create_point(0, 4, -2);
	t_vector direction3 = create_vector(0, -1, 1);
	t_ray ray3 = create_ray(origin3, direction3);

	t_vector origin4 = create_point(0, 0, -2);
	t_vector direction4 = create_vector(0, 1, 2);
	t_ray ray4 = create_ray(origin4, direction4);

	t_vector origin5 = create_point(0, -1, -2);
	t_vector direction5 = create_vector(0, 1, 1);
	t_ray ray5 = create_ray(origin5, direction5);


	// Test the intersection function
	t_list_intersect *intersections1 = intersect_cylinder(cyl, ray1);
	t_list_intersect *intersections2 = intersect_cylinder(cyl, ray2);
	t_list_intersect *intersections3 = intersect_cylinder(cyl, ray3);
	t_list_intersect *intersections4 = intersect_cylinder(cyl, ray4);
	t_list_intersect *intersections5 = intersect_cylinder(cyl, ray5);

	printf("Intersections for ray1:\n\n"); //TODO: this test fail :(
	print_list(&intersections1, 0);
	free_list(&intersections1);
	printf("Intersections for ray2:\n\n");
	print_list(&intersections2, 0);
	free_list(&intersections2);
	printf("Intersections for ray3:\n\n");
	print_list(&intersections3, 0);
	free_list(&intersections3);

	// Print the intersection lists
	printf("Intersections for ray4:\n\n");
	print_list(&intersections4, 0);
	free_list(&intersections4);
	printf("Intersections for ray5:\n\n");
	print_list(&intersections5, 0);
	free_list(&intersections5);
	return 0;
}
*/
