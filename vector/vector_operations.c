/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_operations.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atucci <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/12 14:48:17 by atucci            #+#    #+#             */
/*   Updated: 2025/01/24 16:50:00 by atucci           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

//TODO: STUDY THOSE OPERATIONS
// 1. Vector Addition
t_vector	add(t_vector v1, t_vector v2)
{
	t_vector	result;

	result = default_vector();
	if (is_a_point(v1) && is_a_point(v2))
		return (ft_printf("bad usage adding 2 point\n"), result);
	result.x = v1.x + v2.x;
	result.y = v1.y + v2.y;
	result.z = v1.z + v2.z;
	result.w = v1.w + v2.w;
	return (result);
}

// 2. Vector Subtraction
t_vector	subtract(t_vector v1, t_vector v2)
{
	t_vector	result;

	result = default_vector();
	if (is_a_vector(v1) && is_a_point(v2))
		return (ft_printf("bad subtract vector to a point\n"), result);
	result.x = v1.x - v2.x;
	result.y = v1.y - v2.y;
	result.z = v1.z - v2.z;
	result.w = v1.w - v2.w;
	return (result);
}

// 3. Scalar Multiplication
t_vector	multiplication(t_vector v, double scalar)
{
	t_vector	result;

	result.x = v.x * scalar;
	result.y = v.y * scalar;
	result.z = v.z * scalar;
	result.w = v.w * scalar;
	return (result);
}

// 4. Scalar Division
t_vector	division(t_vector v, double scalar)
{
	t_vector	result;

	result = default_vector();
	if (scalar <= 0.0)
		return (ft_printf("trying to divide by zero\n"), result);
	result.x = v.x / scalar;
	result.y = v.y / scalar;
	result.z = v.z / scalar;
	result.w = v.w / scalar;
	return (result);
}
