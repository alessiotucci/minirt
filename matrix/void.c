/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   void.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atucci <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 16:45:36 by atucci            #+#    #+#             */
/*   Updated: 2024/05/31 11:48:21 by atucci           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../minirt.h"

void	divide_matrix_void(int size, double **source, double det)
{
	int		i;
	int		j;

	i = 0;
	while (i < size)
	{
		j = 0;
		while (j < size)
		{
			source[i][j] /= det;
			j++;
		}
		i++;
	}
}

void	matrix_of_cofactors_void(int size, double **matrix)
{
	int		i;
	int		j;
	double	cof;

	i = 0;
	while (i < size)
	{
		j = 0;
		while (j < size)
		{
			cof = cofactor(i, j, matrix, size);
			matrix[i][j] = cof;
			j++;
		}
		i++;
	}
}

void	transposing_void(int rows, int cols, double **matrix)
{
	int		i;
	int		j;
	double	temp;

	i = 0;
	while (i < rows)
	{
		j = i;
		while (j < cols)
		{
			temp = matrix[i][j];
			matrix[i][j] = matrix[j][i];
			matrix[j][i] = temp;
			j++;
		}
		i++;
	}
}

void	inversing_matrix_void(int size, double **source)
{
	double	det;

	if (is_matrix_invertible(size, source) == 0)
	{
		printf("Cannot reverse it!\n");
		return;
	}
	matrix_of_cofactors_void(size, source);
	transposing(size, size, source);
	det = determinant(source, size);
	divide_matrix_void(size, source, det);
}

