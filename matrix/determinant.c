/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   determinant.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atucci <atucci@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 22:39:46 by atucci            #+#    #+#             */
/*   Updated: 2024/05/28 22:47:56 by atucci           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"
#include <stdlib.h>

// Function to find the cofactor of a matrix
void	find_cofactor(int rows, int cols, double **matrix, double **cofactor, int excludedRow, int excludedCol)
{
	int cofRow = 0, cofCol = 0;
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

