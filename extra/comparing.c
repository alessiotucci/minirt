/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   comparing.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atucci <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 11:57:43 by atucci            #+#    #+#             */
/*   Updated: 2025/02/23 18:03:19 by atucci           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

//Look in the header for the macro defined
// return TRUE (1) if EPISILON IS GREATER, so they are the SAME
// return FALSE (0) if the difference in GREATER than epsilon DIFFERENT
int	comparing_double(double a, double b)
{
	return (fabs(a - b) < EPSILON);
}

int	comparing_vector(t_vector a, t_vector b)
{
	return (comparing_double(a.x, b.x) && comparing_double(a.y, b.y)
		&& comparing_double(a.w, b.w));
}

void	swap_two_doubles(double arr[2])
{
	double	tmp;

	tmp = arr[0];
	arr[0] = arr[1];
	arr[1] = tmp;
}
