/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   determinant.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atucci <atucci@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 22:39:46 by atucci            #+#    #+#             */
/*   Updated: 2024/05/29 10:54:35 by atucci           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"
#include <stdlib.h>

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


/* Function to find the cofactor of a matrix
void	find_cofactor(int rows, int cols, double **matrix, double **cofactor, int excludedRow, int excludedCol)
{
	int	cofRow = 0;
	int	cofCol = 0;
	for (int row = 0; row < rows; row++)
	{
		for (int col = 0; col < cols; col++)
		{
			if (row != excludedRow && col != excludedCol)
			{
				cofactor[cofRow][cofCol++] = matrix[row][col];
				if (cofCol == cols - 1)
				{
					cofCol = 0;
					cofRow++;
				}
			}
		}
	}
}

double	find_determinant(int rows, int cols, double **matrix)
{
	double	det;
	int		sign;
	double	**cofactor;

	sign = 1;
	det = 0;
	if (rows == 1)
		return (matrix[0][0]);
	// The cofactor matrix
	cofactor = (double **)malloc(rows * sizeof(double *));
	for (int i = 0; i < rows; i++)
		cofactor[i] = (double *)malloc(cols * sizeof(double));
	for (int i = 0; i < cols; i++)
	{
		// Getting the cofactor of matrix[0][i]
		find_cofactor(rows, cols, matrix, cofactor, 0, i);
		// Recursively finding the determinant
		det += sign * matrix[0][i] * find_determinant(rows - 1, cols - 1, cofactor);
		sign = -sign;
	}
	for (int i = 0; i < rows; i++)
		free(cofactor[i]);
	free(cofactor);
	return (det);
}

*/
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
	return (0);
}
//TO run the main for testing purpose
//gcc *.c ../libft/libft.a ../extra/comparing.c ../extra/print_debug.c
*/
