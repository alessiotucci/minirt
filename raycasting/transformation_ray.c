/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transformation_ray.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atucci <atucci@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 09:41:01 by atucci            #+#    #+#             */
/*   Updated: 2024/07/26 10:14:20 by atucci           ###   ########.fr       */
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
	return (0);
}

