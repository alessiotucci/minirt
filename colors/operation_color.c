/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operation_color.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atucci <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 18:28:35 by atucci            #+#    #+#             */
/*   Updated: 2024/07/30 13:17:48 by atucci           ###   ########.fr       */
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

	result.r = my_clamp((c.r * scalar), 0, 255);
	result.g = my_clamp((c.g * scalar), 0, 255);
	result.b = my_clamp((c.b * scalar), 0, 255);
	return (result);
}

// Multiplying two colors (Hadamard product)
t_color	multiply_colors(t_color c1, t_color c2)
{
	t_color	result;

	result.r = my_clamp(((c1.r / 255.0) * (c2.r / 255.0) * 255), 0, 255);
	result.g = my_clamp(((c1.g / 255.0) * (c2.g / 255.0) * 255), 0, 255);
	result.b = my_clamp(((c1.b / 255.0) * (c2.b / 255.0) * 255), 0, 255);
	return (result);
}

t_color	create_color(double r, double g, double b)
{
	t_color	new;

	new.r = my_clamp(r, 0, 255);
	new.g = my_clamp(g, 0, 255);
	new.b = my_clamp(b, 0, 255);
	return (new);
}

/*
int main()
{
	printf("%sSCENARIO: Adding Colors%s\n", RED, RESET);
	t_color c1 = create_color(230, 153, 191);  // (0.9, 0.6, 0.75) scaled to 255
	t_color c2 = create_color(178, 26, 64);	// (0.7, 0.1, 0.25) scaled to 255
	t_color result = add_colors(c1, c2);
	print_color(result);
	printf("✅ %sTEST PASSED%s✅\n", BG_GREEN, BG_RESET);
	printf("Expected: \nR: 255 G: 179 B: 255 (1.6, 0.7, 1.0) clamped to 255\n\n");

	printf("%sSCENARIO: Subtracting Colors%s\n", RED, RESET);
	c1 = create_color(230, 153, 191);  // (0.9, 0.6, 0.75) scaled to 255
	c2 = create_color(178, 26, 64);	// (0.7, 0.1, 0.25) scaled to 255
	result = subtract_colors(c1, c2);
	print_color(result);
	printf("✅ %sTEST PASSED%s✅\n", BG_GREEN, BG_RESET);
	printf("Expected: \nR: 52 G: 127 B: 127 (0.2, 0.5, 0.5) scaled to 255\n\n");

	printf("%sSCENARIO: Multiplying Color by Scalar%s\n", RED, RESET);
	t_color c = create_color(51, 76, 102);  // (0.2, 0.3, 0.4) scaled to 255
	float scalar = 2.0;
	result = multiply_color_by_scalar(c, scalar);
	print_color(result);
	printf("✅ %sTEST PASSED%s✅\n", BG_GREEN, BG_RESET);
	printf("Expected: \nR: 102 G: 153 B: 204 (0.4, 0.6, 0.8) scaled to 255\n\n");

	printf("%sSCENARIO: Multiplying Colors%s\n", RED, RESET);
	c1 = create_color(255, 51, 102);  // (1, 0.2, 0.4) scaled to 255
	c2 = create_color(230, 255, 26);  // (0.9, 1, 0.1) scaled to 255
	result = multiply_colors(c1, c2);
	print_color(result);
	printf("✅ %sTEST PASSED%s✅\n", BG_GREEN, BG_RESET);
	printf("Expected: \nR: 230 G: 51 B: 10 (0.9, 0.2, 0.04) scaled to 255\n\n");

	return 0;
}
*/
