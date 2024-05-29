/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   determinant.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atucci <atucci@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 22:39:46 by atucci            #+#    #+#             */
/*   Updated: 2024/05/29 14:58:31 by atucci           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"
#include <stdlib.h>

double	determinant(double **matrix, int size)
{
	if (size == 2)
		return (determinant_two(matrix));
	else
		return (determinant_n(matrix, size));
}

//1
double	determinant_two(double **matrix)
{
	return ((matrix[0][0] * matrix[1][1]) - (matrix[0][1] * matrix[1][0]));
}

//2
/* The minor of an element at row i and column j is the determinant of the 
 * submatrix at (i, j). */
double	minor(int row, int col, double **matrix, int size)
{
	double	**find;

	find = submatrix(row, col, matrix, size);
	return (determinant(find, size - 1));
}

//3
double	cofactor(int row, int col, double **matrix, int size)
{
	double	result;

	result = minor(row, col, matrix, size);
	if ((row + col) % 2 == 0)
		return (result);
	else
		return (result * -1);
}

//4
double	**submatrix(int index_rows, int index_cols, double **matrix, int size)
{
	int		i;
	int		j;
	int		row;
	int		col;
	double	**new;

	new = create_matrix(size - 1, size - 1);
	init_heap_matrix(size - 1, size - 1, new);
	i = 0;
	row = 0;
	while (i < size)
	{
		if (i != index_rows)
		{
			j = 0;
			col = 0;
			while (j < size)
			{
				if (j != index_cols)
				{
					new[row][col] = matrix[i][j];
					col++;
				}
				j++;
			}
			row++;
		}
		i++;
	}
	return (new);
}

//5
double	determinant_n(double **matrix, int size)
{
	double	result;
	int		i;

	i = 0;
	result = 0.0;
	while (i < size)
	{
		//printf("result: %f += cofactor:(%f) * matrix[0][%d]: (%f)\n", result, cofactor(0, i , matrix, size), i,  matrix[0][i]);
		result += cofactor(0, i , matrix, size) * matrix[0][i];
		i++;
	}
	return (result);

}
/*Main to test out the function
int main()
{
	double	**a;
	double	**b;
	a = create_matrix(4, 4);
	init_heap_matrix(4, 4, a);
	a[0][0] = -6.0; a[0][1] = 1.0; a[0][2] = 1.0; a[0][3] = 6.0;
	a[1][0] = -8.0; a[1][1] = 5.0; a[1][2] = 8.0; a[1][3] = 6.0;
	a[2][0] = -1.0; a[2][1] = 0.0; a[2][2] = 8.0; a[2][3] = 2.0;
	a[3][0] = -7.0; a[3][1] = 1.0; a[3][2] = -1.0; a[3][3] = 1.0;
	
	printf("Matrix a\n");
	print_int_matrix(4, 4, a);
	b = submatrix(2, 1, a, 4);

	printf("b = submatrix(2, 1, a, 4);\n");
	printf("Matrix b\n");
	print_int_matrix(3, 3, b);

	double	**z;
	z = create_matrix(2, 2);
	init_heap_matrix(2, 2, z);
	z[0][0] = 1.0; z[0][1] = 5.0;
	z[1][0] = -3.0; z[1][1] = 2.0;
	printf("the determinant of 2x2 matrix z is [%f]\n", determinant_two(z));
	printf("***\n");

	double **x;
	x = create_matrix(3, 3);
	init_heap_matrix(3, 3, x);
	x[0][0] = 3.0; x[0][1] = 5.0; x[0][2] = 0.0;
	x[1][0] = 2.0; x[1][1] = -1.0; x[1][2] = -7.0;
	x[2][0] = 6.0; x[2][1] = -1.0; x[2][2] = 5.0;
	printf("the minor of the 3x3 matrix x is [%f]\n", minor(1, 0, x, 3));

	double **t;
	t = create_matrix(3, 3);
	init_heap_matrix(3, 3, t);
	t[0][0] = 3.0; t[0][1] = 5.0; t[0][2] = 0.0;
	t[1][0] = 2.0; t[1][1] = -1.0; t[1][2] = -7.0;
	t[2][0] = 6.0; t[2][1] = -1.0; t[2][2] = 5.0;
	printf("the minor of the 3x3 matrix T is [%f]\n", minor(0, 0, t, 3));
	printf("the cofactor of the 3x3 matrix T is [%f]\n", cofactor(0, 0, t, 3));
	printf("the minor of the 3x3 matrix T is [%f]\n", minor(1, 0, t, 3));
	printf("the cofactor of the 3x3 matrix T is [%f]\n", cofactor(1, 0, t, 3));

	printf("** matrix y ***\n");
	double	**y;
	y = create_matrix(4, 4);
	init_heap_matrix(4, 4, y);
	y[0][0] = -2.0; y[0][1] = -8.0; y[0][2] = 3.0; y[0][3] = 5.0;
	y[1][0] = -3.0; y[1][1] = 1.0; y[1][2] = 7.0; y[1][3] = 3.0;
	y[2][0] = 1.0; y[2][1] = 2.0; y[2][2] = -9.0; y[2][3] = 6.0;
	y[3][0] = -6.0; y[3][1] = 7.0; y[3][2] = 7.0; y[3][3] = -9.0;
	printf("determinant of matrix Y: [%f]\n", determinant_n(y, 4));
	printf("DEBUG: cofactor of matrix Y: {%f}\n", cofactor(0, 0, y, 4));
	return (0);
}
*/
//TO run the main for testing purpose
//gcc *.c ../libft/libft.a ../extra/comparing.c ../extra/print_debug.c

