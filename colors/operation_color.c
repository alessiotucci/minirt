/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operation_color.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atucci <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 18:28:35 by atucci            #+#    #+#             */
/*   Updated: 2024/05/25 09:52:04 by atucci           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

// Adding two colors
t_color	add_colors(t_color c1, t_color c2)
{
	t_color	result;

	result.r = my_clamp(c1.r + c2.r, 0, 255);
	result.g = my_clamp(c1.g + c2.g, 0, 255);
	result.b = my_clamp(c1.b + c2.b, 0, 255);
	return (result);
}

// Subtracting two colors
t_color	subtract_colors(t_color c1, t_color c2)
{
	t_color	result;

	result.r = my_clamp(c1.r - c2.r, 0, 255);
	result.g = my_clamp(c1.g - c2.g, 0, 255);
	result.b = my_clamp(c1.b - c2.b, 0, 255);
	return (result);
}

// Multiplying a color by a scalar
t_color	multiply_color_by_scalar(t_color c, float scalar)
{
	t_color	result;

	result.r = my_clamp((int)(c.r * scalar), 0, 255);
	result.g = my_clamp((int)(c.g * scalar), 0, 255);
	result.b = my_clamp((int)(c.b * scalar), 0, 255);
	return (result);
}

// Multiplying two colors (Hadamard product)
t_color multiply_colors(t_color c1, t_color c2)
{
	t_color	result;

	result.r = my_clamp((int)((c1.r / 255.0) * (c2.r / 255.0) * 255), 0, 255);
	result.g = my_clamp((int)((c1.g / 255.0) * (c2.g / 255.0) * 255), 0, 255);
	result.b = my_clamp((int)((c1.b / 255.0) * (c2.b / 255.0) * 255), 0, 255);
	return (result);
}
