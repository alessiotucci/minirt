/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   translations.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atucci <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 15:15:48 by atucci            #+#    #+#             */
/*   Updated: 2025/02/19 15:10:45 by atucci           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

//TODO this is weird!
//double	**inversing_matrix(int size, double **source);

void	last_cols_value(int size, double **matrix, t_vector source)
{
	matrix[0][size - 1] = source.x;
	matrix[1][size - 1] = source.y;
	matrix[2][size - 1] = source.z;
}

double	**create_translation_matrix(t_vector move)
{
	double	**matrix;

	matrix = malloc_matrix(4, 4);
	create_identity_matrix(matrix);
	last_cols_value(4, matrix, move);
	return (matrix);
}

t_vector	translations(t_vector move, t_vector origin)
{
	double		**matrix;
	t_vector	vector;

	matrix = malloc_matrix(4, 4);
	create_identity_matrix(matrix);
	last_cols_value(4, matrix, move);
	vector = matrix_x_vector(matrix, origin);
	free_heap_matrix(matrix, 4);
	return (vector);
}

t_vector	inverse_translations(t_vector move, t_vector origin)
{
	double		**matrix;
	t_vector	vector;

	matrix = malloc_matrix(4, 4);
	create_identity_matrix(matrix);
	last_cols_value(4, matrix, move);
	inversing_matrix_void(4, matrix);
	vector = matrix_x_vector(matrix, origin);
	free_heap_matrix(matrix, 4);
	return (vector);
}
//TODO: DOUBLE CHECK THIS PART pls

/*
int	main()
{
	printf("%sTEST 1%s\n", RED, RESET);
	t_vector	trans = create_point(5, -3, 2);
	t_vector	point = create_point(-3.0, 4.0, 5.0);

	t_vector	vector = create_vector(-3.0, 4.0, 5.0);

	t_vector	result = translations(trans, point);
	printf("the result of the operations is ");
	print_vector(result);
	printf("\n%sTEST 2%s\n", RED, RESET);
	t_vector	result1 = inverse_translations(trans, point);
	printf("the result of the operations is ");
	print_vector(result1);
	printf("\n%sTEST 3%s\n", RED, RESET);
	t_vector	result2 = translations(trans, vector);
	printf("the result of the operations is ");
	print_vector(result2);
}
*/
//TODO: CHECK THE LEAKS WITH THIS COMMANDS
//valgrind   --leak-check=full --show-leak-kinds=all ./a.out
