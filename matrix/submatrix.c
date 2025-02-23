/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   submatrix.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atucci <atucci@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 14:59:42 by atucci            #+#    #+#             */
/*   Updated: 2025/02/23 18:52:28 by atucci           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

static void	fill_submatrix(double **new, double **matrix, int size, int *idx)
{
	int	i;
	int	j;
	int	row;
	int	col;

	row = 0;
	i = 0;
	while (i < size)
	{
		if (i != idx[0])
		{
			col = 0;
			j = 0;
			while (j < size)
			{
				if (j != idx[1])
					new[row][col++] = matrix[i][j];
				j++;
			}
			row++;
		}
		i++;
	}
}

double	**submatrix(int index_rows, int index_cols, double **matrix, int size)
{
	double	**new;
	int		idx[2];

	new = malloc_matrix(size - 1, size - 1);
	init_heap_matrix(size - 1, size - 1, new);
	idx[0] = index_rows;
	idx[1] = index_cols;
	fill_submatrix(new, matrix, size, idx);
	return (new);
}
