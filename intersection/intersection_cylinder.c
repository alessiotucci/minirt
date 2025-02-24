/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersection_cylinder.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atucci <atucci@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 13:27:39 by atucci            #+#    #+#             */
/*   Updated: 2025/02/24 17:48:10 by atucci           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

//5
static	void	add_lateral_intersection(t_list_intersect **list,
					t_cylinder *cylinder, t_ray ray, double t_val)
{
	t_vector		intersect_point;
	double			project;
	t_intersection	inter;

	intersect_point = add(ray.origin, multiplication(ray.direction, t_val));
	project = dot(subtract(intersect_point, cylinder->center), cylinder->axis);
	if (project >= cylinder->min && project <= cylinder->max)
	{
		inter = intersection(t_val, cylinder->identifier, cylinder);
		add_intersection_l(list, &inter);
	}
}

//4
static	void	solve_quadratic_equation(double a, double b,
					double c, double roots[3])
{
	double	disc;

	disc = pow(b, 2) - (4 * a * c);
	if (disc < 0)
	{
		roots[0] = 0;
		return ;
	}
	roots[0] = 1;
	roots[1] = (-b - sqrt(disc)) / (2 * a);
	roots[2] = (-b + sqrt(disc)) / (2 * a);
}

//3
static	void	compute_cylinder_quadratic_coeff(double coeff[3],
					t_cylinder *cylinder, t_ray ray)
{
	t_vector	vec_from_center;
	t_vector	ray_dir_perp;
	t_vector	vec_perp;

	vec_from_center = subtract(ray.origin, cylinder->center);
	ray_dir_perp = subtract(ray.direction, multiplication(cylinder->axis,
				dot(ray.direction, cylinder->axis)));
	vec_perp = subtract(vec_from_center, multiplication(cylinder->axis,
				dot(vec_from_center, cylinder->axis)));
	coeff[0] = dot(ray_dir_perp, ray_dir_perp);
	coeff[1] = 2 * dot(ray_dir_perp, vec_perp);
	coeff[2] = dot(vec_perp, vec_perp) - pow(cylinder->diameter / 2, 2);
}

//2) called
static	t_ray	transform_ray_to_object_space(t_cylinder *cylinder, t_ray ray)
{
	double	**transform_copy;
	double	**inv_matrix;
	t_ray	object_ray;

	transform_copy = copy_matrix(4, 4, cylinder->transform);
	inv_matrix = inversing_matrix(4, transform_copy);
	free_heap_matrix(transform_copy, 4);
	object_ray = transform_ray(ray, inv_matrix);
	free_heap_matrix(inv_matrix, 4);
	return (object_ray);
}

//1
/* main function */
t_list_intersect	*intersect_cylinder(t_cylinder *cylinder, t_ray old_ray)
{
	t_list_intersect	*list;
	t_ray				object_ray;
	double				coeff[3];
	double				roots[3];

	list = NULL;
	object_ray = transform_ray_to_object_space(cylinder, old_ray);
	compute_cylinder_quadratic_coeff(coeff, cylinder, object_ray);
	if (comparing_double(coeff[0], 0.0))
		return (NULL);
	solve_quadratic_equation(coeff[0], coeff[1], coeff[2], roots);
	if ((int)roots[0] == 0)
		return (NULL);
	add_lateral_intersection(&list, cylinder, object_ray, roots[1]);
	add_lateral_intersection(&list, cylinder, object_ray, roots[2]);
	intersect_caps(*cylinder, object_ray, &list);
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
