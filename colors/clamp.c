/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clamp.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atucci <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 09:40:30 by atucci            #+#    #+#             */
/*   Updated: 2025/02/24 17:03:29 by atucci           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

// Helper function to clamp a value within a specified range
double	my_clamp(double value, double min_val, double max_val)
{
	if (value < min_val)
		return (min_val);
	else if (value > max_val)
		return (max_val);
	else
		return (value);
}

// Clamps a vector's magnitude to a maximum value.
t_vector	clamp_delta(t_vector delta, double max_val)
{
	double	mag;
	double	factor;

	mag = magnitude(delta);
	if (mag > max_val)
	{
		factor = max_val / mag;
		return (multiplication(delta, factor));
	}
	return (delta);
}
