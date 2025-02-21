/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotations.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atucci <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 15:16:40 by atucci            #+#    #+#             */
/*   Updated: 2025/02/19 15:10:31 by atucci           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

//TODO: leaks!
t_vector	rotation_x(t_vector origin, double radians)
{
	double		**matrix;
	t_vector	vector;

	matrix = matrix_rotation_x(radians);
	vector = matrix_x_vector(matrix, origin);
	free_heap_matrix(matrix, 4);
	return (vector);
}

t_vector	rotation_y(t_vector origin, double radians)
{
	double		**matrix;
	t_vector	vector;

	matrix = matrix_rotation_y(radians);
	vector = matrix_x_vector(matrix, origin);
	free_heap_matrix(matrix, 4);
	return (vector);
}

t_vector	rotation_z(t_vector origin, double radians)
{
	double		**matrix;
	t_vector	vector;

	matrix = matrix_rotation_z(radians);
	vector = matrix_x_vector(matrix, origin);
	free_heap_matrix(matrix, 4);
	return (vector);
}

/*main to test out the function */
/*
int	main()
{
	t_vector	point_x = create_point(0, 1, 0);
	t_vector	result_x = rotation_x(point_x, M_PI / 4);
	printf("%sRESULT 1: rotation around X axis%s\n", RED, RESET);
	print_vector(result_x);
	t_vector	result0 = rotation_x(point_x, M_PI / 2);
	printf("%sRESULT 2: rotation around X axis%s\n", RED, RESET);
	print_vector(result0);

	t_vector	point_y = create_point(0, 0, 1);
	t_vector	result_y = rotation_y(point_y, M_PI / 4);
	printf("%sRESULT 1: rotation around Y axis%s\n", YELLOW, RESET);
	print_vector(result_y);
	t_vector	result1 = rotation_y(point_y, M_PI / 2);
	printf("%sRESULT 2: rotation around Y axis%s\n", YELLOW, RESET);
	print_vector(result1);

	t_vector	point_z = create_point(0, 1, 0);
	t_vector	result_z = rotation_z(point_z, M_PI / 4);
	printf("%sRESULT 1: rotation around Z axis%s\n", GREEN, RESET);
	print_vector(result_z);
	t_vector	result3 = rotation_z(point_z, M_PI / 2);
	printf("%sRESULT 2: rotation around Z axis%s\n",  GREEN, RESET);
	print_vector(result3);

	return (0);
}
*/
//TODO: CHECK THE LEAKS WITH THIS COMMANDS
//valgrind   --leak-check=full --show-leak-kinds=all ./a.out
