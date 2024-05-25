/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize_matrix.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atucci <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 18:49:23 by atucci            #+#    #+#             */
/*   Updated: 2024/05/25 19:21:22 by atucci           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

void	copy_row_value(double destination[4], double source[4])
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
	copy_row_value(new[0], a);
	copy_row_value(new[1], b);
	copy_row_value(new[2], c);
	copy_row_value(new[3], d);
	return (new);
}

int	main(void)
{
	double	a[4];
	double	b[4];
	double	c[4];
	double	d[4];

	a[0] = 1.0;
	a[1] = 2.0;
	a[2] = 3.0;
	a[3] = 4.0;
	b[0] = 5.0;
	b[1] = 6.0;
	b[2] = 7.0;
	b[3] = 8.0;
	c[0] = 9.0;
	c[1] = 10.0;
	c[2] = 11.0;
	c[3] = 12.0;
	d[0] = 13.0;
	d[1] = 14.0;
	d[2] = 15.0;
	d[3] = 16.0;
	print_int_matrix(4, 4, value_matrix(a, b, c, d));
	return (0);
}