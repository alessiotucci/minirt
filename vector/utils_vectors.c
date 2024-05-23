/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_vectors.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atucci <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 11:19:53 by atucci            #+#    #+#             */
/*   Updated: 2024/05/23 11:54:23 by atucci           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

int	is_a_point(t_vector vect)
{
	return (vect.w == 1.0)
}

int	is_a_vector(t_vector vect)
{
	return (vect.w == 0.0)
}

t_vector	create_point(double x, double y, double z)
{
	t_vector	vector;

	vector.x = x;
	vector.y = y;
	vector.z = z;
	vector.w = 1.0;
	return (vector);
}

t_vector	create_vector(double x, double y, double z)
{
	t_vector	vector;

	vector.x = x;
	vector.y = y;
	vector.z = z;
	vector.w = 0.0;
	return (vector);
}
