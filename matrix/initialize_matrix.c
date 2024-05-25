/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize_matrix.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atucci <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 18:49:23 by atucci            #+#    #+#             */
/*   Updated: 2024/05/25 19:11:15 by atucci           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

static void	copy_value(double destination[4], double source[4])
{
	int	i;

	i = 0;
	while (i < 4)
	{
		destination[i] = source[i];
		i++;
	}
}

double	**value_matrix(double a[4], double b[4], double c[4], double d[4])
{
	double	**new;
	int		i;
	int		j;

	i = 0;
	new = create_matrix(4, 4);
	init_heap_matrix(4, 4, new);
	copy_value(new[0], a);
	copy_value(new[1], b);
	copy_value(new[2], c);
	copy_value(new[3], d);
	return (new);
}

int	main()
{
	double a[4] = {1.0, 2.0, 3.0, 4.0};
	double b[4] = {5.0, 6.0, 7.0, 8.0};
	double c[4] = {9.0, 10.0, 11.0, 12.0};
	double d[4] = {13.0, 14.0, 15.0, 16.0};

	print_int_matrix(4, 4, value_matrix(a, b, c, d));
	return 0;
}
