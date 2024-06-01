/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   translations.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atucci <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 15:15:48 by atucci            #+#    #+#             */
/*   Updated: 2024/06/01 18:36:23 by atucci           ###   ########.fr       */
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

t_vector	translations(t_vector move, t_vector origin)
{
	//1) Create an identity matrix
	double	**matrix;

	matrix = create_matrix(4, 4);
	create_identity_matrix(matrix);
	//2) add the value to the last columns
	last_cols_value(4, matrix, move);
	//3) Multiply the origin by the matrix
	return (matrix_x_vector(matrix, origin));
}

t_vector	inverse_translations(t_vector move, t_vector origin)
{
	double	**matrix;
	//double	**rev_matrix;

	matrix = create_matrix(4, 4);
	create_identity_matrix(matrix);
	last_cols_value(4, matrix, move);
	//rev_matrix = inversing_matrix(4, matrix);
	inversing_matrix_void(4, matrix);
//	printf("VOID\n");
//	print_int_matrix(4, 4, matrix);
//	printf("***\n");
//	printf("DOUBLE **\n");
//	print_int_matrix(4, 4, rev_matrix);
	//4) Multiply the origin by the reverse matrix
	return (matrix_x_vector(matrix, origin));
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
// gcc ../matrix/*.c ../vector/*.c translations.c  ../extra/comparing.c ../extra/print_debug.c  ../libft/libft.a -lm
//TODO: CHECK THE LEAKS WITH THIS COMMANDS
//valgrind   --leak-check=full --show-leak-kinds=all ./a.out
