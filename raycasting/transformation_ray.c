/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transformation_ray.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atucci <atucci@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 09:41:01 by atucci            #+#    #+#             */
/*   Updated: 2024/07/26 12:28:08 by atucci           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

/* This function return a new ray */
t_ray	transform_ray(t_ray original, double **matrix)
{
	t_ray	new;

	new.origin = matrix_x_vector(matrix, original.origin);
	new.direction = matrix_x_vector(matrix, original.direction);
	return (new);
}

void	set_sphere_transformations(t_sphere *sphere, double **new)
{
	if (sphere->transform)
		free_heap_matrix(sphere->transform, 4);
	sphere->transform = new;
}

int	main()
{
	// Test: Translating a ray
	printf("%sTEST 1%s\n", RED, RESET);

	// Given r ← ray(point(1, 2, 3), vector(0, 1, 0))
	t_vector	origin = create_point(1, 2, 3);
	t_vector	direction = create_vector(0, 1, 0);
	t_ray		r = create_ray(origin, direction);

	// And m ← translation(3, 4, 5)
	t_vector move = create_vector(3, 4, 5);
	double **matrix_t = create_translation_matrix(move);

	t_vector move1 = create_vector(2, 3, 4);
	double **matrix_s = create_scaling_matrix(move1);

	// When r2 ← transform(r, m)
	t_ray r2 = transform_ray(r, matrix_t);
	t_ray r3 = transform_ray(r, matrix_s);
	printf("Matrix Translations\n");
	print_ray(r2);
	printf("%sTEST 2%s\n", RED, RESET);
	printf("Matrix Scaling\n");
	print_ray(r3);

	// Clean up
	free_heap_matrix(matrix_t, 4);
	free_heap_matrix(matrix_s, 4);

	// create unit sphere
	t_color bogus;
	bogus.r = 0; bogus.g = 0; bogus.b = 0;
	t_vector p = create_point(0, 0, 0);
	t_sphere a = create_sphere("sp", p, 1.0, bogus);


	printf("\n\n%sSCENARIO:%sA sphere default transformations\n", RED, RESET);
	printf("sphere [a] has default matrix\n");
	print_int_matrix(4, 4, a.transform);

	printf("\n\n%sSCENARIO:%sChanging a sphere default transformation\n", RED, RESET);
	double **matrix = create_translation_matrix(move1);
	set_sphere_transformations(&a, matrix);
	printf("sphere [a] has setted the NEW matrix\n");
	print_int_matrix(4, 4, a.transform);

	printf("\n\n%sSCENARIO:%sIntersecting a scaled sphere with a ray\n", RED, RESET);
	t_vector	o = create_point(0, 0, -5);
	t_vector	d = create_vector(0, 0, 1);
	t_ray		ri = create_ray(o, d);
	t_vector move2 = create_vector(2, 2, 2);
	set_sphere_transformations(&a, (create_scaling_matrix(move2)));
	printf("Intersection list value ...\n");
	t_intersection_list *res1 = intersect_sphere(a, ri);
	print_intersection_list(res1);
	printf("❌ %sTEST FAILED%s❌\n", BG_RED, BG_RESET);
	//printf("✅ %sTEST PASSED%s✅\n", BG_GREEN, BG_RESET);
	
	printf("\n\n%sSCENARIO:%sIntersecting a translated sphere with a ray\n", RED, RESET);
	t_vector move3 = create_vector(5, 0, 0);
	set_sphere_transformations(&a, (create_translation_matrix(move3)));
	printf("Intersection list value ...\n");
	t_intersection_list *res2 = intersect_sphere(a, ri);
	print_intersection_list(res2);
	printf("❌ %sTEST FAILED%s❌\n", BG_RED, BG_RESET);
	//printf("✅ %sTEST PASSED%s✅\n", BG_GREEN, BG_RESET);

	return (0);
}
