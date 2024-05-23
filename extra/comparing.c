/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   comparing.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atucci <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 11:57:43 by atucci            #+#    #+#             */
/*   Updated: 2024/05/23 13:40:54 by atucci           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

//Look in the header for the macro defined
int	comparing_double(double a, double b)
{
	return (fabs(a - b) < EPSILON);
}

int	comparing_vector(t_vector a, t_vector b)
{
	return (comparing_double(a.x, b.x) && comparing_double(a.y, b.y)
			&& comparing_double(a.w, b.w));
}
