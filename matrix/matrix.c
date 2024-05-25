/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atucci <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 16:25:08 by atucci            #+#    #+#             */
/*   Updated: 2024/05/25 18:42:30 by atucci           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

//5
void	free_heap_matrix(double **matrix, int rows)
{
	int	i;

	i = 0;
	while (i < rows)
		free(matrix[i++]);
	free(matrix);
}

//4
double	**create_matrix(int rows, int col)
{
	double	**new_matrix;
	int	i;

	i = 0;
	new_matrix = (double **)malloc(rows * sizeof(double *));
	while (i < rows)
	{
		new_matrix[i] = (double *)malloc(col * sizeof(double));
		i++;
	}
	return (new_matrix);
}

//3
void	print_int_matrix(int rows, int cols, double **matrix)
{
	int	i;
	int	j;

	i = 0;
	while (i < rows)
	{
		j = 0;
		while (j < cols)
		{
			printf("[%f] ", matrix[i][j]);
			j++;
		}
	printf("\n");
	i++;
	}
	printf("***\n");
}

//2
// Function to create and initialize a matrix of given size
void	init_matrix(int rows, int cols, double matrix[rows][cols])
{
	int	i;
	int	j;

	i = 0;
	while (i < rows)
	{
		j = 0;
		while (j < cols)
		{
			matrix[i][j] = 0.0;
			j++;
		}
		i++;
	}
}

void	init_heap_matrix(int rows, int cols, double **matrix)
{
	int	i;
	int	j;

	i = 0;
	while (i < rows)
	{
		j = 0;
		while (j < cols)
		{
			matrix[i][j] = 0.0;
			j++;
		}
		i++;
	}
}

/*
int main()
{
	// Declare the matrix with automatic storage duration (stack-allocated)
	double	my_matrix[4][4];
	int	j;
	int	i;
	double	**other_matrix;

	other_matrix = create_matrix(4, 4);
	init_matrix(4, 4, my_matrix);
	my_matrix[1][2] = 42.2;
	init_heap_matrix(4, 4, other_matrix);
	other_matrix[1][2] = -1.1;
	i = 0;
	while (i < 4)
	{
		j = 0;
		while (j < 4)
		{
			printf("[%f] ", my_matrix[i][j]);
			j++;
		}
		printf("\n");
		i++;
	}
	printf("\n\n");
	print_int_matrix(4, 4, other_matrix);
	free_heap_matrix(other_matrix, 4);
	return (0);
}
*/
