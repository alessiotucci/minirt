/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scaling.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atucci <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 15:17:11 by atucci            #+#    #+#             */
/*   Updated: 2024/06/01 14:58:24 by atucci           ###   ########.fr       */
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

t_vector	scaling(t_vector move, t_vector origin)
{
	double	**matrix;

	matrix = create_matrix(4, 4);
	identity_value_matrix(matrix, move);
	return (matrix_x_vector(matrix, origin));
}

t_vector	scaling_inverse(t_vector move, t_vector origin)
{
	double	**matrix;
	double	**inversed;
	matrix = create_matrix(4, 4);
	identity_value_matrix(matrix, move);
	printf("scaling matrix \n");
	print_int_matrix(4, 4, matrix);
	inversed = inversing_matrix(4, matrix);
	inversing_matrix_void(4, matrix);
	//return (matrix_x_vector(matrix, origin));
	return (matrix_x_vector(inversed, origin));
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
	t_vector result0 = scaling_inverse(scal, point);
	print_vector(result0);
	
	t_vector neg = create_point(-1, 1, 1);
	t_vector point2 = create_point(2, 3, 4);
	printf("%sTEST 2 SCALING%s\n", RED, RESET);
	t_vector result1 = scaling_inverse(neg, point2);
	print_vector(result1);

	return (0);
}
*/
//gcc ../matrix/*.c ../vector/*.c scaling.c  ../extra/comparing.c ../extra/print_debug.c  ../libft/libft.a -lm

