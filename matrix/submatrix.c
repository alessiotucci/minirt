/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   submatrix.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atucci <atucci@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 14:59:42 by atucci            #+#    #+#             */
/*   Updated: 2025/02/19 15:04:33 by atucci           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

//5

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
