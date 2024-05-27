/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operations_matrix.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atucci <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 20:52:18 by atucci            #+#    #+#             */
/*   Updated: 2024/05/27 12:46:18 by atucci           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

//TODO: Remember that comparing doubles ain't that easy
// if return (1) is true
int	comparing_heap_matrix(int rows, int cols, double **a, double **b)
{
	int	i;
	int	j;

	i = 0;
	while (i < rows)
	{
		j = 0;
		while (j < cols)
		{
			//if (a[i][j] != b[i][j])
			if (comparing_double(a[i][j], b[i][j]) == 0)
				return (1); // are different
			j++;
		}
		i++;
	}
	return (0); // are equals
}

static double	*oper(double *line, double **matrix_a, double **matrix_b, int index)
{
	int	i;
	int	j;

	i = 0;
	while (i < 4)
	{
		line[i] = 0;
		j = 0;
		while (j < 4)
		{
			line[i] += matrix_a[index][j] * matrix_b[j][index];
			j++;
		}
		i++;
	}
	return (line);
}

double	**multiply_matrix(int cols_a, int rows_b, double **a, double **b)
{
	double	**new;
	double	new_a[4];
	double	new_b[4];
	double	new_c[4];
	double	new_d[4];

	new = create_matrix(4, 4);
	if (cols_a != rows_b)
		return (ft_printf("You dont know how to multiply matrix\n"), new);
	init_heap_matrix(4, 4, new);
	copy_row_value(new[0], oper(new_a, a, b, 0));
	copy_row_value(new[1], oper(new_b, a, b, 1));
	copy_row_value(new[2], oper(new_c, a, b, 2));
	copy_row_value(new[3], oper(new_d, a, b, 3));
	return (new);

}

/*Main to test out the function
int main()
{
	double	**a;
	double	**b;

	a = create_matrix(4, 4);
	init_heap_matrix(4, 4, a);
	b = create_matrix(4, 4);
	init_heap_matrix(4, 4, b);
	//a[1][2] = -1.1;
	printf("1: NOT THE SAME\n0: are the same!\n");
	printf("\n\n");
	printf("comparison result: %d\n", comparing_heap_matrix(4, 4, a, b));
	//print_int_matrix(4, 4, a);
	free_heap_matrix(a, 4);
	free_heap_matrix(b, 4);
	return (0);
}*/


/* Main to test out the function
int	main()
{

	double a_values[4][4] =
	{
		{1.0, 2.0, 3.0, 4.0},
		{5.0, 6.0, 7.0, 8.0},
		{9.0, 10.0, 11.0, 12.0},
		{13.0, 14.0, 15.0, 16.0}
	};

	double b_values[4][4] =
	{
		{17.0, 18.0, 19.0, 20.0},
		{21.0, 22.0, 23.0, 24.0},
		{25.0, 26.0, 27.0, 28.0},
		{29.0, 30.0, 31.0, 32.0}
	return (0);
} */
