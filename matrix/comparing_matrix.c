/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   comparing_matrix.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atucci <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 20:52:18 by atucci            #+#    #+#             */
/*   Updated: 2024/05/26 21:36:55 by atucci           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

// 1 is true
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
