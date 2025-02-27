/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   complex_operations.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atucci <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 15:42:04 by atucci            #+#    #+#             */
/*   Updated: 2025/02/27 15:08:45 by atucci           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

// 2. Normalization
t_vector	normalization(t_vector vector)
{
	t_vector	new_vector;

	new_vector = default_vector();
	if (magnitude(vector) == 0)
	{
		ft_printf("%smagnitude is zero!%s\n", RED, RESET);
		return (new_vector);
	}
	new_vector.x = vector.x / magnitude(vector);
	new_vector.y = vector.y / magnitude(vector);
	new_vector.z = vector.z / magnitude(vector);
	new_vector.w = vector.w / magnitude(vector);
	return (new_vector);
}

// 3. Magnitude
double	magnitude(t_vector v)
{
	return (sqrt((v.x * v.x) + (v.y * v.y) + (v.z * v.z) + (v.w * v.w)));
}

// 4. Dot Product
double	dot(t_vector a, t_vector b)
{
	return (a.x * b.x + a.y * b.y + a.z * b.z + a.w * b.w);
}

// 5. Cross Product
t_vector	cross(t_vector a, t_vector b)
{
	t_vector	result;

	result.x = a.y * b.z - a.z * b.y;
	result.y = a.z * b.x - a.x * b.z;
	result.z = a.x * b.y - a.y * b.x;
	return (result);
}
