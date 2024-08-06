/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shearing.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atucci <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 13:41:57 by atucci            #+#    #+#             */
/*   Updated: 2024/08/06 12:13:31 by atucci           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

//TODO: check the leaks with this command
// valgrind   --leak-check=full --show-leak-kinds=all ./a.out
t_vector	shearing(t_vector origin, double value[6])
{
	double		**matrix;
	t_vector	result;

	matrix = malloc_matrix(4, 4);
	create_identity_matrix(matrix);
	matrix[0][1] = value[0];
	matrix[0][2] = value[1];
	matrix[1][0] = value[2];
	matrix[1][2] = value[3];
	matrix[2][0] = value[4];
	matrix[2][1] = value[5];
	result = matrix_x_vector(matrix, origin);
	return (free_heap_matrix(matrix, 4), result);
}

/* this is a main to test */
/*
int	main()
{
	t_vector	point = create_point(2, 3, 4);
	double	test[6];
	test[0] = 1.0; test[1] = 0.0; test[2] = 0.0; test[3] = 0.0;test[4] = 0.0; test[5] = 0.0;
	t_vector result = shearing(point, test);
	printf("TEST 0:\n");
	print_vector(result);

	double	test1[6];
	test1[0] = 0.0; test1[1] = 1.0; test1[2] = 0.0; test1[3] = 0.0;test1[4] = 0.0; test1[5] = 0.0;
	t_vector result1 = shearing(point, test1);
	printf("TEST 1:\n");
	print_vector(result1);

	double	test2[6];
	test2[0] = 0.0; test2[1] = 0.0; test2[2] = 1.0; test2[3] = 0.0;test2[4] = 0.0; test2[5] = 0.0;
	t_vector result2 = shearing(point, test2);
	printf("TEST 2:\n");
	print_vector(result2);

	double	test3[6];
	test3[0] = 0.0; test3[1] = 0.0; test3[2] = 0.0; test3[3] = 1.0;test3[4] = 0.0; test3[5] = 0.0;
	t_vector result3 = shearing(point, test3);
	printf("TEST 3:\n");
	print_vector(result3);

	double	test4[6];
	test4[0] = 0.4; test4[1] = 0.0; test4[2] = 0.0; test4[3] = 0.0;test4[4] = 1.0; test4[5] = 0.0;
	t_vector result4 = shearing(point, test4);
	printf("TEST 4:\n");
	print_vector(result4);

	double	test5[6];
	test5[0] = 0.0; test5[1] = 0.0; test5[2] = 0.0; test5[3] = 0.0;test5[4] = 0.0; test5[5] = 1.0;
	t_vector result5 = shearing(point, test5);
	printf("TEST 5:\n");
	print_vector(result5);

	return (0);
}
*/
// gcc ../matrix/*.c ../vector/*.c shearing.c  ../extra/comparing.c ../extra/print_debug.c  ../libft/libft.a -lm

