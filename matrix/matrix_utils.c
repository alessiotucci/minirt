/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftroise <ftroise@student.42roma.it>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 16:25:08 by atucci            #+#    #+#             */
/*   Updated: 2024/12/20 13:51:27 by ftroise          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

//5
/*void	free_heap_matrix(double **matrix, int rows)
{
	int	i;

	i = 0;
	if (matrix == NULL)
		return (error_msg("FREE_HEAP_MATRIX-> failure\n"));
	while (i < rows)
		free(matrix[i++]);
	free(matrix);
}*/

void free_heap_matrix(double **matrix, int size)
{
	int i;
	i = 0;

    if (!matrix)
		return; // Evita di liberare memoria nulla

    while (i < size)
	{
        if (matrix[i])
		{
            free(matrix[i]);
            matrix[i] = NULL; // Evita doppi free
        }
        i++;
    }
    free(matrix);
}


//4) you can decide rows and cols!
/*double	**malloc_matrix(int rows, int col) ORIFINALE
{
	double	**new_matrix;
	int	i, j;

	// Allocazione dell'array di puntatori
	new_matrix = (double **)malloc(rows * sizeof(double *));
	if (!new_matrix)
	{
		perror("Failed to allocate memory for matrix rows");
		return NULL;
	}

	// Allocazione delle righe
	for (i = 0; i < rows; i++)
	{
		new_matrix[i] = (double *)malloc(col * sizeof(double));
		if (!new_matrix[i])
		{
			perror("Failed to allocate memory for matrix columns");

			// Se fallisce, liberare la memoria già allocata
			for (int k = 0; k < i; k++)
			{
				free(new_matrix[k]);
			}
			free(new_matrix);
			return NULL;
		}

		// Inizializzare la matrice a zero
		for (j = 0; j < col; j++)
		{
			new_matrix[i][j] = 0.0;
		}
	}

	return new_matrix;
}*/

double **malloc_matrix(long unsigned int rows, int col)
{
    if (rows <= 0 || col <= 0) {
        fprintf(stderr, "Invalid matrix dimensions: rows=%ld, col=%d\n", rows, col);
        return NULL;
    }

    if (rows > SIZE_MAX / col) {
        fprintf(stderr, "Matrix size too large: rows=%ld, col=%d\n", rows, col);
        return NULL;
    }

    double **new_matrix = NULL;
    double *data = NULL;

    // Allocazione dell'array di puntatori
    new_matrix = (double **)malloc(rows * sizeof(double *));
    if (!new_matrix) {
        perror("Failed to allocate memory for matrix rows");
        return NULL;
    }

    // Allocazione contigua per i dati della matrice
    data = (double *)calloc(rows * col, sizeof(double));
    if (!data) {
        perror("Failed to allocate memory for matrix data");
        free(new_matrix);
        return NULL;
    }

    // Collegare i puntatori di riga ai dati
    for (long unsigned int i = 0; i < rows; i++) {
        new_matrix[i] = &data[i * col];
    }

    return new_matrix;
}

// Funzione per liberare la memoria allocata
void free_matrix(double **matrix) {
    if (matrix) {
        free(matrix[0]); // Libera il blocco contiguo
        free(matrix);    // Libera l'array di puntatori
    }
}



//3
void	print_int_matrix(int rows, int cols, double **matrix)
{
	int	i;
	int	j;

	if (matrix == NULL)
		return ;
	i = 0;
	while (i < rows)
	{
		j = 0;
		while (j < cols)
		{
			printf(" | %f | ", matrix[i][j]);
			j++;
		}
	printf("\n");
	i++;
	}
	printf("***\n");
}

//2
// Function to create and initialize a matrix of given size
void	init_zero_matrix(int rows, int cols, double matrix[rows][cols])
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

/* you can decide rows and cols! */
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
 * to test the code: 'gcc matrix.c -o test'
 *
int main()
{
	// Declare the matrix with automatic storage duration (stack-allocated)
	double	my_matrix[4][4];
	int	j;
	int	i;
	double	**other_matrix;

	other_matrix = malloc_matrix(4, 4);
	init_zero_matrix(4, 4, my_matrix);
	my_matrix[1][2] = 42.2;
	init_heap_matrix(4, 4, other_matrix);
	other_matrix[1][2] = -1.1;
	i = 0;
	while (i < 4)
	{
		j = 0;
		while (j < 4)
		{
			printf(" | %f | ", my_matrix[i][j]);
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
//TODO: CHECK THE LEAKS WITH THIS COMMANDS
//valgrind   --leak-check=full --show-leak-kinds=all ./a.out
