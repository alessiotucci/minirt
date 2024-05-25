/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atucci <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 16:25:08 by atucci            #+#    #+#             */
/*   Updated: 2024/05/25 17:20:39 by atucci           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
int	**create_matrix(int rows, int col)
{
	int	**new_matrix;
	int	i;

	i = 0;
	new_matrix = (int **)malloc(rows * sizeof(int *));
	while (i < rows)
	{
		new_matrix[i] = (int *)malloc(col * sizeof(int));
		i++;
	}
	return (new_matrix);
}

// Function to create and initialize a matrix of given size
void	init_matrix(int rows, int cols, int matrix[rows][cols])
{
	int	i;
	int	j;

	i = 0;
	while (i < rows)
	{
		j = 0;
		while (j < cols)
		{
			matrix[i][j] = 0;
			j++;
		}
		i++;
	}
}

int main()
{
	// Declare the matrix with automatic storage duration (stack-allocated)
	int	my_matrix[4][4];
	int	j;
	int	i;
	int	**other_matrix;

	other_matrix = create_matrix(4, 4);
	init_matrix(4, 4, my_matrix);
	my_matrix[1][2] = 42;
	other_matrix[1][2] = -1;
	i = 0;
	while (i < 4)
	{
		j = 0;
		while (j < 4)
		{
			printf("[%d] ", my_matrix[i][j]);
			j++;
		}
		printf("\n");
		i++;
	}
	printf("\n\n");
	i = 0;
	while (i < 4)
	{
		j = 0;
		while (j < 4)
		{
			printf("[%d] ", other_matrix[i][j]);
			j++;
		}
		printf("\n");
		i++;
	}

	return (0);
}

