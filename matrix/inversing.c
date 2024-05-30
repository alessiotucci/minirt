/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inversing.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atucci <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 14:39:34 by atucci            #+#    #+#             */
/*   Updated: 2024/05/29 19:24:54 by atucci           ###   ########.fr       */
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
	print_int_matrix(4, 4, inversed);
	return (inversed);
}
/* main to test out the function */
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
	double	**k;
	k = create_matrix(4, 4);
	init_heap_matrix(4, 4, k);
	k[0][0] = -5.0; k[0][1] = 2.0; k[0][2] = 6.0; k[0][3] = -8.0;
	k[1][0] = 1.0; k[1][1] = -5.0; k[1][2] = 1.0; k[1][3] = 8.0;
	k[2][0] = 7.0; k[2][1] = 7.0; k[2][2] = -6.0; k[2][3] = -7.0;
	k[3][0] = 1.0; k[3][1] = -3.0; k[3][2] = 7.0; k[3][3] = 4.0;

	printf("determinant k: [%f]\n", determinant(k, 4));
	double **inversed = inversing_matrix(4, k);
	print_int_matrix(4, 4, inversed);

	printf("%sTEST 2%s\n", RED, RESET);
	double	**r;
	r = create_matrix(4, 4);
	init_heap_matrix(4, 4, r);
	r[0][0] = 8.0; r[0][1] = -5.0; r[0][2] = 9.0; r[0][3] = 2.0;
	r[1][0] = 7.0; r[1][1] = 5.0; r[1][2] = 6.0; r[1][3] = 1.0;
	r[2][0] = -6.0; r[2][1] = 0.0; r[2][2] = 9.0; r[2][3] = 6.0;
	r[3][0] = -3.0; r[3][1] = 0.0; r[3][2] = -9.0; r[3][3] = -4.0;
	printf("determinant r: [%f]\n", determinant(r, 4));
	double **inversed1 = inversing_matrix(4, r);
	print_int_matrix(4, 4, inversed1);


	printf("%sTEST 3%s\n", RED, RESET);
	double	**e;
	e = create_matrix(4, 4);
	init_heap_matrix(4, 4, e);
	e[0][0] = -5.0; e[0][1] = 2.0; e[0][2] = 6.0; e[0][3] = -8.0;
	e[1][0] = 1.0; e[1][1] = -5.0; e[1][2] = 1.0; e[1][3] = 8.0;
	e[2][0] = 7.0; e[2][1] = 7.0; e[2][2] = -6.0; e[2][3] = -7.0;
	e[3][0] = 1.0; e[3][1] = -3.0; e[3][2] = 7.0; e[3][3] = 4.0;
	printf("determinant e: [%f]\n", determinant(e, 4));
	double **inversed2 = inversing_matrix(4, e);
	print_int_matrix(4, 4, inversed2);


	return (0);
}
