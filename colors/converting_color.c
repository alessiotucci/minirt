/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   converting_color.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atucci <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 12:43:40 by atucci            #+#    #+#             */
/*   Updated: 2024/08/01 11:04:10 by atucci           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"
#include <stdio.h>

// Function to convert color components from [0, 1] range to [0, 255] range
double convert_component(double component)
{
	double value;

	value = component * 255.0;
	return my_clamp(value, 0, 255);
}

// Function to convert a color from [0, 1] range to [0, 255] range
t_color convert_color(t_color old)
{
	t_color color;

	color.r = convert_component(old.r);
	color.g = convert_component(old.g);
	color.b = convert_component(old.b);
	return color;
}

// Function to convert color components from [0, 255] range to [0, 1] range
double convert_component_inverse(double component)
{
	return my_clamp(component / 255.0, 0, 1);
}

// Function to convert a color from [0, 255] range to [0, 1] range
t_color convert_color_inverse(t_color color)
{
	t_color result;

	result.r = convert_component_inverse(color.r);
	result.g = convert_component_inverse(color.g);
	result.b = convert_component_inverse(color.b);
	return result;
}

/*
int main()
{
	printf("values, %lf, %lf, %lf\n", 0.5, 0.4, 0.1);
	t_color color1 = create_color(0.5, 0.4, 0.1);
	printf("BEFORE: color_1\n");
	print_color(color1);
	t_color color = convert_color(color1);
	printf("AFTER Converted Color:\n");
	print_color(color);
	printf("Expected: R: 128 G: 102 B: 26\n");

	printf("***\n\n\n\n***\n");

	t_color color_255 = create_color(128, 102, 26);
	printf("BEFORE: color_255\n");
	print_color(color_255);
	t_color color_1 = convert_color_inverse(color_255);
	printf("AFTER Converted Color:\n");
	print_color(color_1);
	printf("Expected: R: 0.502 G: 0.400 B: 0.102\n");

	printf("***\n\n\n\n***\n");

	// Additional test cases
	t_color color2 = create_color(1.9, 1.9, 1.9);
	printf("BEFORE: color_2\n");
	print_color(color2);
	t_color color2_converted = convert_color(color2);
	printf("AFTER Converted Color:\n");
	print_color(color2_converted);
	printf("Expected: R: 484 G: 484 B: 484\n");

	t_color color3 = create_color();
	printf("BEFORE: color_3\n");
	print_color(color3);
	t_color color3_converted = convert_color(color3);
	printf("AFTER Converted Color:\n");
	print_color(color3_converted);

	t_color color4 = create_color();
	printf("BEFORE: color_4\n");
	print_color(color4);
	t_color color4_converted = convert_color_inverse(color4);
	printf("AFTER Converted Color:\n");
	print_color(color4_converted);

	return 0;
}
*/
