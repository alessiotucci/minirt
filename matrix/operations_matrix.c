/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operations_matrix.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atucci <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 20:52:18 by atucci            #+#    #+#             */
/*   Updated: 2024/05/27 18:59:02 by atucci           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

//TODO: Remember that comparing doubles ain't that easy
// if return (1) is true

//1
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
			if (comparing_double(a[i][j], b[i][j]) == 0)
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}

//2
double	**multiply_matrix(int cols_a, int rows_b, double **a, double **b)
{
	double	**new;
	int		i;
	int		j;

	new = create_matrix(4, 4);
	if (cols_a != rows_b)
		return (ft_printf("You dont know how to multiply matrix\n"), new);
	init_heap_matrix(4, 4, new);
	i = 0;
	while (i < 4)
	{
		j = 0;
		while (j < 4)
		{
			new[i][j] = ((a[i][0] * b[0][j]) + (a[i][1] * b[1][j])
					+ (a[i][2] * b[2][j]) + (a[i][3] * b[3][j]));
			j++;
		}
		i++;
	}
	return (new);
}

//3
t_vector	matrix_x_vector(double **a, t_vector b)
{
	t_vector	result;

	result.x = a[0][0] * b.x + a[0][1] * b.y + a[0][2] * b.z + a[0][3] * b.w;
	result.y = a[1][0] * b.x + a[1][1] * b.y + a[1][2] * b.z + a[1][3] * b.w;
	result.z = a[2][0] * b.x + a[2][1] * b.y + a[2][2] * b.z + a[2][3] * b.w;
	result.w = a[3][0] * b.x + a[3][1] * b.y + a[3][2] * b.z + a[3][3] * b.w;

	return (result);
}

//4
void	create_identity_matrix(double	**ret)
{
	int	i;
	int	j;

	i = 0;
	while (i < 4)
	{
		j = 0;
		while (j < 4)
		{
			if (i == j)
				ret[i][j] = 1.0;
			else
				ret[i][j] = 0.0;
			j++;
		}
		i++;
	}
}

//5
double	**transposing(int rows, int cols, double **matrix)
{
	double	**ret;
	int		i;
	int		j;

	ret = create_matrix(rows, cols);
	init_heap_matrix(rows, cols, ret);
	i = 0;
	while (i < rows)
	{
		j = 0;
		while (j < cols)
		{
			ret[i][j] = matrix[j][i];
			j++;
		}
		i++;
	}
	return (ret);
}

/*Main to test out the function
int main()
{
	double	**a;
	double	**b;
	double	**c;

	//test identity matrix
	double	**identity = create_matrix(4, 4);
	create_identity_matrix(identity);
	printf("INDENTITY MATRIX\n");
	print_int_matrix(4, 4, identity);

	double	**d;
	d = create_matrix(4, 4);
	init_heap_matrix(4, 4, d);
	t_vector	e;
	a = create_matrix(4, 4);
	init_heap_matrix(4, 4, a);
	b = create_matrix(4, 4);
	init_heap_matrix(4, 4, b);
	a[0][0] = 1.0; a[0][1] = 4.0; a[0][2] = 4.0; a[0][3] = 4.0;
	a[1][0] = 1.0; a[1][1] = 1.0; a[1][2] = 1.0; a[1][3] = 1.0;
	a[2][0] = 3.0; a[2][1] = 0.0; a[2][2] = 0.0; a[2][3] = 6.0;
	a[3][0] = 1.2; a[3][1] = 1.2; a[3][2] = 1.2; a[3][3] = 1.0;

	b[0][0] = 1.0; b[0][1] = 4.0; b[0][2] = 4.0; b[0][3] = 4.0;
	b[1][0] = 1.0; b[1][1] = 1.0; b[1][2] = 1.0; b[1][3] = 1.0;
	b[2][0] = 1.0; b[2][1] = 6.0; b[2][2] = 6.0; b[2][3] = 2.0;
	b[3][0] = 1.0; b[3][1] = 1.0; b[3][2] = 1.0; b[3][3] = 1.0;

	//test transposint
	double	**trans = transposing(4, 4, a);
	printf("matrix a:\n");
	print_int_matrix(4, 4, a);
	printf("matrix trans:\n");
	print_int_matrix(4, 4, trans);
	return (0);

	e.x = 1.0; e.y = 2.0; e.z = 3.0; e.w = 1.0;
	d[0][0] = 1.0; d[0][1] = 2.0; d[0][2] = 3.0; d[0][3] = 4.0;
	d[1][0] = 2.0; d[1][1] = 4.0; d[1][2] = 4.0; d[1][3] = 2.0;
	d[2][0] = 8.0; d[2][1] = 6.0; d[2][2] = 4.0; d[2][3] = 1.0;
	d[3][0] = 0.0; d[3][1] = 0.0; d[3][2] = 0.0; d[3][3] = 1.0;

	printf("Matrix d X vector e\n");
	t_vector result = matrix_x_vector(d, e);
	print_vector(result);
	//printf("1: NOT THE SAME\n0: are the same!\n");
	//printf("\n\n");
	//printf("comparison result: %d\n", comparing_heap_matrix(4, 4, a, b));
	//print_int_matrix(4, 4, a);
	printf("*\t*\t\n");
	//print_int_matrix(4, 4, b);
	print_int_matrix(4, 4, identity);
	//printf("*\t*\t\n");
	c = multiply_matrix(4, 4, a, identity);
	print_int_matrix(4, 4, c);
	printf("1: NOT THE SAME\n0: are the same!\n");
	printf("comparison result: %d\n", comparing_heap_matrix(4, 4, a, c));
	//print_int_matrix(4, 4, a);
	//free_heap_matrix(c, 4);
	//free_heap_matrix(a, 4);
	//free_heap_matrix(b, 4);
	return (0);
}
//TO run the main for testing purpose
//gcc *.c ../libft/libft.a ../extra/comparing.c ../extra/print_debug.c
*/
