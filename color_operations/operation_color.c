/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operation_color.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atucci <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 18:28:35 by atucci            #+#    #+#             */
/*   Updated: 2024/05/24 18:29:29 by atucci           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

//TODO: FUCK TERNARIES
// Adding two colors
t_color add_colors(t_color c1, t_color c2)
{
	t_color result;
	result.r = c1.r + c2.r > 255 ? 255 : c1.r + c2.r;
	result.g = c1.g + c2.g > 255 ? 255 : c1.g + c2.g;
	result.b = c1.b + c2.b > 255 ? 255 : c1.b + c2.b;
	return result;
}

// Subtracting two colors
t_color subtract_colors(t_color c1, t_color c2)
{
	t_color result;
	result.r = c1.r - c2.r < 0 ? 0 : c1.r - c2.r;
	result.g = c1.g - c2.g < 0 ? 0 : c1.g - c2.g;
	result.b = c1.b - c2.b < 0 ? 0 : c1.b - c2.b;
	return result;
}

// Multiplying a color by a scalar
t_color multiply_color_by_scalar(t_color c, float scalar)
{
	t_color result;
	result.r = c.r * scalar > 255 ? 255 : c.r * scalar;
	result.g = c.g * scalar > 255 ? 255 : c.g * scalar;
	result.b = c.b * scalar > 255 ? 255 : c.b * scalar;
	return result;
}

// Multiplying two colors (Hadamard product)
t_color multiply_colors(t_color c1, t_color c2)
{
	t_color result;
	result.r = (c1.r / 255.0) * (c2.r / 255.0) * 255;
	result.g = (c1.g / 255.0) * (c2.g / 255.0) * 255;
	result.b = (c1.b / 255.0) * (c2.b / 255.0) * 255;
	return result;
}

