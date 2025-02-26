/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scaling.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftroise <ftroise@student.42roma.it>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 15:17:11 by atucci            #+#    #+#             */
/*   Updated: 2025/02/19 15:09:33 by atucci           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

void	identity_value_matrix(double **matrix, t_vector source)
{
	create_identity_matrix(matrix);
	matrix[0][0] = source.x;
	matrix[1][1] = source.y;
	matrix[2][2] = source.z;
}

/*TODO: this has to be done for each transformation */
double	**create_scaling_matrix(t_vector move)
{
	double		**matrix;

	matrix = malloc_matrix(4, 4);
	identity_value_matrix(matrix, move);
	return (matrix);
}

t_vector	scaling(t_vector move, t_vector origin)
{
	double		**matrix;
	t_vector	result;

	matrix = malloc_matrix(4, 4);
	identity_value_matrix(matrix, move);
	result = matrix_x_vector(matrix, origin);
	return (free_heap_matrix(matrix, 4), result);
}

t_vector	scaling_inverse(t_vector move, t_vector origin)
{
	double		**matrix;
	double		**inversed;
	t_vector	result;

	matrix = malloc_matrix(4, 4);
	identity_value_matrix(matrix, move);
	inversed = inversing_matrix(4, matrix);
	free_heap_matrix(matrix, 4);
	result = matrix_x_vector(inversed, origin);
	return (free_heap_matrix(inversed, 4), result);
}
/*
int	main()
{
	t_vector point = create_point(-4, 6, 8);
	t_vector scal = create_point(2, 3, 4);
	printf("%sTEST 1 SCALING%s\n", RED, RESET);
	t_vector result = scaling(scal, point);
	print_vector(result);
	printf("%sTEST 2 SCALING%s\n", RED, RESET);
	t_vector result0 = (scal, point);
	print_vector(result0);
	
	t_vector neg = create_point(-1, 1, 1);
	t_vector point2 = create_point(2, 3, 4);
	printf("%sTEST 2 SCALING%s\n", RED, RESET);
	t_vector result1 = scaling_inverse(neg, point2);
	print_vector(result1);

	return (0);
}
*/
//TODO: CHECK THE LEAKS WITH THIS COMMANDS
//valgrind   --leak-check=full --show-leak-kinds=all ./a.out
