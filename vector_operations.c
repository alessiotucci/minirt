/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_operations.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atucci <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/12 14:48:17 by atucci            #+#    #+#             */
/*   Updated: 2024/05/12 14:57:01 by atucci           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
// Function to calculate dot product of two vectors
double	dot(t_vector v1, t_vector v2)
{
	return (v1.x * v2.x + v1.y * v2.y + v1.z * v2.z);
}

// Function to subtract two vectors
t_vector	subtract(t_vector v1, t_vector v2)
{
	t_vector	result;

	result.x = v1.x - v2.x;
	result.y = v1.y - v2.y;
	result.z = v1.z - v2.z;
	return (result);
}

// Function to convert color struct to int
int	create_trgb(t_color color)
{
	return (0 << 24 | color.r << 16 | color.g << 8 | color.b);
}
