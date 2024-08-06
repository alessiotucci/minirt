/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   determinant.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atucci <atucci@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 22:39:46 by atucci            #+#    #+#             */
/*   Updated: 2024/08/06 12:52:19 by atucci           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"
#include <stdlib.h>

//1
double	determinant_two(double **matrix)
{
	return (matrix[0][0] * matrix[1][1]) - (matrix[0][1] * matrix[1][0]);
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
		result += cofactor(0, i , matrix, size) * matrix[0][i];
		i++;
	}
	return (result);
}

/* as you can see, now Determinant() free the matrix! */
double	determinant(double **matrix, int size)
{
	double	result;

	if (size == 2)
		result = (determinant_two(matrix));
	else
		result = (determinant_n(matrix, size));
	return (free_heap_matrix(matrix, size), result);
}

//2
/* The minor of an element at row i and column j is the determinant of the 
 * submatrix at (i, j). */
double	minor(int row, int col, double **matrix, int size)
{
	double	**find;
	double	result;

	find = submatrix(row, col, matrix, size);
	result = determinant(find, size - 1);
	//free_heap_matrix(find, 4);
	return (result);
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

	new = malloc_matrix(size - 1, size - 1);
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

/*Main to test out the function
int main()
{
	double	**a;
	double	**b;
	a = malloc_matrix(4, 4);
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

	free_heap_matrix(a, 4);
	free_heap_matrix(b, 3);

	double	**z;
	z = malloc_matrix(2, 2);
	init_heap_matrix(2, 2, z);
	z[0][0] = 1.0; z[0][1] = 5.0;
	z[1][0] = -3.0; z[1][1] = 2.0;
	printf("the determinant of 2x2 matrix z is [%f]\n", determinant_two(z));
	printf("***\n");
	free_heap_matrix(z, 2);

	double **x;
	x = malloc_matrix(3, 3);
	init_heap_matrix(3, 3, x);
	x[0][0] = 3.0; x[0][1] = 5.0; x[0][2] = 0.0;
	x[1][0] = 2.0; x[1][1] = -1.0; x[1][2] = -7.0;
	x[2][0] = 6.0; x[2][1] = -1.0; x[2][2] = 5.0;
	printf("the minor of the 3x3 matrix x is [%f]\n", minor(1, 0, x, 3));
	free_heap_matrix(x, 3);

	double **t;
	t = malloc_matrix(3, 3);
	init_heap_matrix(3, 3, t);
	t[0][0] = 3.0; t[0][1] = 5.0; t[0][2] = 0.0;
	t[1][0] = 2.0; t[1][1] = -1.0; t[1][2] = -7.0;
	t[2][0] = 6.0; t[2][1] = -1.0; t[2][2] = 5.0;
	printf("the minor of the 3x3 matrix T is [%f]\n", minor(0, 0, t, 3));
	printf("the cofactor of the 3x3 matrix T is [%f]\n", cofactor(0, 0, t, 3));
	printf("the minor of the 3x3 matrix T is [%f]\n", minor(1, 0, t, 3));
	printf("the cofactor of the 3x3 matrix T is [%f]\n", cofactor(1, 0, t, 3));
	free_heap_matrix(t, 3);

	printf("** matrix y ***\n");
	double	**y;
	y = malloc_matrix(4, 4);
	init_heap_matrix(4, 4, y);
	y[0][0] = -2.0; y[0][1] = -8.0; y[0][2] = 3.0; y[0][3] = 5.0;
	y[1][0] = -3.0; y[1][1] = 1.0; y[1][2] = 7.0; y[1][3] = 3.0;
	y[2][0] = 1.0; y[2][1] = 2.0; y[2][2] = -9.0; y[2][3] = 6.0;
	y[3][0] = -6.0; y[3][1] = 7.0; y[3][2] = 7.0; y[3][3] = -9.0;
	printf("determinant of matrix Y: [%f]\n", determinant_n(y, 4));
	printf("DEBUG: cofactor of matrix Y: {%f}\n", cofactor(0, 0, y, 4));
	free_heap_matrix(y, 4);
	return (0);
}
*/

//TODO: CHECK THE LEAKS WITH THIS COMMANDS
//valgrind   --leak-check=full --show-leak-kinds=all ./a.out
