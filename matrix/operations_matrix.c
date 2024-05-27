/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operations_matrix.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atucci <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 20:52:18 by atucci            #+#    #+#             */
/*   Updated: 2024/05/27 16:40:30 by atucci           ###   ########.fr       */
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
			if (comparing_double(a[i][j], b[i][j]) == 0)
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}

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

/*Main to test out the function
int main()
{
	double	**a;
	double	**b;
	double	**c;

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
	//printf("1: NOT THE SAME\n0: are the same!\n");
	//printf("\n\n");
	//printf("comparison result: %d\n", comparing_heap_matrix(4, 4, a, b));
	//print_int_matrix(4, 4, a);
	print_int_matrix(4, 4, a);
	printf("*\t*\t\n");
	print_int_matrix(4, 4, b);
	printf("*\t*\t\n");
	c = multiply_matrix(4, 4, a, b);
	print_int_matrix(4, 4, c);
	free_heap_matrix(c, 4);
	free_heap_matrix(a, 4);
	free_heap_matrix(b, 4);
	return (0);
}
*/
//TO run the main for testing purpose
//gcc *.c ../libft/libft.a ../extra/comparing.c

