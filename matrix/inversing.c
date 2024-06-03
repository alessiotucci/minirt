/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inversing.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atucci <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 14:39:34 by atucci            #+#    #+#             */
/*   Updated: 2024/06/01 18:36:55 by atucci           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

//1 return 1 (true) if it is possible to invert the matrix
//remember how to compare doubles
int	is_matrix_invertible(int size, double **matrix)
{
	if (comparing_double(determinant(matrix, size), 0.0))
		return (0);
	else
		return (1);
}

double	**divide_matrix(int size, double **source, double det)
{
	double	**new;
	int		i;
	int		j;

	new = create_matrix(size, size);
	init_heap_matrix(size, size, new);
	i = 0;
	while (i < size)
	{
		j = 0;
		while (j < size)
		{
			new[i][j] = source[i][j] / det;
			j++;
		}
		i++;
	}
	return (new);
}

double	**matrix_of_cofactors(int size, double **matrix)
{
	double	**new;
	int		i;
	int		j;

	new = create_matrix(size, size);
	init_heap_matrix(size, size, new);
	i = 0;
	while (i < size)
	{
		j = 0;
		while (j < size)
		{
			new[i][j] = cofactor(i, j, matrix, size);
			j++;
		}
		i++;
	}
	return (new);
}

double	**transposing(int rows, int cols, double **matrix)
{
	double	**ret;
	int		i;
	int		j;

	ret = create_matrix(rows, cols);
	init_heap_matrix(rows, cols, ret);
	i = 0;
	while (i < rows)
	{
		j = 0;
		while (j < cols)
		{
			ret[i][j] = matrix[j][i];
			j++;
		}
		i++;
	}
	return (ret);
}

double	**inversing_matrix(int size, double **source)
{
	double	**mat_cofact;
	double	**trans;
	double	**inversed;

	if (is_matrix_invertible(size, source) == 0)
		return (printf("Cannot reverse it!\n"), source);
	mat_cofact = matrix_of_cofactors(size, source);
	trans = transposing(size, size, mat_cofact);
	inversed = divide_matrix(size, trans, determinant(source, size));
	return (inversed);
}
/* main to test out the function */
/*
int	main()
{
	printf("** matrix y ***\n");
	double	**y;
	y = create_matrix(4, 4);
	init_heap_matrix(4, 4, y);
	y[0][0] = 6.0; y[0][1] = 4.0; y[0][2] = 4.0; y[0][3] = 4.0;
	y[1][0] = 5.0; y[1][1] = 5.0; y[1][2] = 7.0; y[1][3] = 6.0;
	y[2][0] = 4.0; y[2][1] = -9.0; y[2][2] = 3.0; y[2][3] = -7.0;
	y[3][0] = 9.0; y[3][1] = 1.0; y[3][2] = 7.0; y[3][3] = -6.0;
	if (is_matrix_invertible(4, y))
	{
		printf("nice! it can be invert!\n");
		printf("determinant y: [%f]\n", determinant(y, 4));
	}
	else
		printf("It cannot be reverse\n");
	printf("\n\n** matrix x ***\n");
	double	**x;
	x = create_matrix(4, 4);
	init_heap_matrix(4, 4, x);
	x[0][0] = -4.0; x[0][1] = 2.0; x[0][2] = -2.0; x[0][3] = -3.0;
	x[1][0] = -9.0; x[1][1] = 6.0; x[1][2] = 2.0; x[1][3] = 6.0;
	x[2][0] = 0.0; x[2][1] = -5.0; x[2][2] = 1.0; x[2][3] = -5.0;
	x[3][0] = 0.0; x[3][1] = 0.0; x[3][2] = 0.0; x[3][3] = 0.0;
	if (is_matrix_invertible(4, x))
		printf("nice! it can be invert!\n");
	else
		printf("It cannot be reverse\n");
	
	printf("%sTEST 1%s\n", RED, RESET);
	printf("Calculating the inverse of another matrix: [k]\n");
	double	**k;
	k = create_matrix(4, 4);
	init_heap_matrix(4, 4, k);
	k[0][0] = -5.0; k[0][1] = 2.0; k[0][2] = 6.0; k[0][3] = -8.0;
	k[1][0] = 1.0; k[1][1] = -5.0; k[1][2] = 1.0; k[1][3] = 8.0;
	k[2][0] = 7.0; k[2][1] = 7.0; k[2][2] = -6.0; k[2][3] = -7.0;
	k[3][0] = 1.0; k[3][1] = -3.0; k[3][2] = 7.0; k[3][3] = 4.0;
	print_int_matrix(4, 4, k);
	printf("determinant k: [%f]\n", determinant(k, 4));
	double **inversed = inversing_matrix(4, k);
	print_int_matrix(4, 4, inversed);

	printf("%sTEST: 2%s\n", RED, RESET);
	printf("Calculating the inverse of another matrix: [r]\n");
	double	**r;
	r = create_matrix(4, 4);
	init_heap_matrix(4, 4, r);
	r[0][0] = 8.0; r[0][1] = -5.0; r[0][2] = 9.0; r[0][3] = 2.0;
	r[1][0] = 7.0; r[1][1] = 5.0; r[1][2] = 6.0; r[1][3] = 1.0;
	r[2][0] = -6.0; r[2][1] = 0.0; r[2][2] = 9.0; r[2][3] = 6.0;
	r[3][0] = -3.0; r[3][1] = 0.0; r[3][2] = -9.0; r[3][3] = -4.0;
	print_int_matrix(4, 4, r);
	printf("determinant r: [%f]\n", determinant(r, 4));
	double **inversed1 = inversing_matrix(4, r);
	print_int_matrix(4, 4, inversed1);


	printf("%sTEST 3%s\n", RED, RESET);
	printf("Calculating the inverse of another matrix: [e]\n");
	double	**e;
	e = create_matrix(4, 4);
	init_heap_matrix(4, 4, e);
	e[0][0] = 9.0; e[0][1] = 3.0; e[0][2] = 0.0; e[0][3] = 9.0;
	e[1][0] = -5.0; e[1][1] = -2.0; e[1][2] = -6.0; e[1][3] = -3.0;
	e[2][0] = -4.0; e[2][1] = 9.0; e[2][2] = 6.0; e[2][3] = 4.0;
	e[3][0] = -7.0; e[3][1] = 6.0; e[3][2] = 6.0; e[3][3] = 2.0;
	print_int_matrix(4, 4, e);
	printf("determinant e: [%f]\n", determinant(e, 4));
	double **inversed2 = inversing_matrix(4, e);
	print_int_matrix(4, 4, inversed2);


	printf("%sTEST 3 %s multiplying a product by its inverse\n", GREEN, RESET);
	printf("Given the following 4x4 matrix a1\n");
	double	**a1;
	a1 = create_matrix(4, 4);
	init_heap_matrix(4, 4, a1);
	a1[0][0] = 9.0; a1[0][1] = 3.0; a1[0][2] = 0.0; a1[0][3] = 9.0;
	a1[1][0] = -5.0; a1[1][1] = -2.0; a1[1][2] = -6.0; a1[1][3] = -3.0;
	a1[2][0] = -4.0; a1[2][1] = 9.0; a1[2][2] = 6.0; a1[2][3] = 4.0;
	a1[3][0] = -7.0; a1[3][1] = 6.0; a1[3][2] = 6.0; a1[3][3] = 2.0;
	print_int_matrix(4, 4, a1);

	printf("And the following matrix 4x4 b1\n");
	double	**b1;
	b1 = create_matrix(4, 4);
	init_heap_matrix(4, 4, b1);
	b1[0][0] = 9.0; b1[0][1] = 3.0; b1[0][2] = 0.0; b1[0][3] = 9.0;
	b1[1][0] = -5.0; b1[1][1] = -2.0; b1[1][2] = -6.0; b1[1][3] = -3.0;
	b1[2][0] = -4.0; b1[2][1] = 9.0; b1[2][2] = 6.0; b1[2][3] = 4.0;
	b1[3][0] = -7.0; b1[3][1] = 6.0; b1[3][2] = 6.0; b1[3][3] = 2.0;
	print_int_matrix(4, 4, b1);

	printf("The matrix C1 is the result of a1 * b1\n");
	double **c1 = multiply_matrix(4, 4, a1, b1);
	print_int_matrix(4, 4, c1);

	printf("Then the c1 * inverse(B) is going to be equal to a1\n");
	double **inverse_b1 = inversing_matrix(4, b1);
	double **result = multiply_matrix(4, 4, c1, inverse_b1);
	printf("comparing matrix result with a1: ");
	if (comparing_heap_matrix(4, 4, result, a1))
		printf("they different!\n");
	else
		printf("they the same\n");
	return (0);
}
*/
//TODO: CHECK THE LEAKS WITH THIS COMMANDS
//valgrind   --leak-check=full --show-leak-kinds=all ./a.out