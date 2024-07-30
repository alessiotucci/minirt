/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   converting_color.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atucci <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 12:43:40 by atucci            #+#    #+#             */
/*   Updated: 2024/07/30 14:16:57 by atucci           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"
#include <stdio.h>

// Function to convert color components from [0, 1] range to [0, 255] range
int	convert_component(float component)
{
	int	value;

	value = (int)(component * 255.0);
	return (my_clamp(value, 0, 255));
}

// Function to convert a color from [0, 1] range to [0, 255] range
t_color	convert_color(t_color old)
{
	t_color	color;

	color.r = convert_component(old.r);
	color.g = convert_component(old.g);
	color.b = convert_component(old.b);
	return (color);
}

// Function to convert color components from [0, 255] range to [0, 1] range
float	convert_component_inverse(int component)
{
	return (component / 255.0);
}

// Function to convert a color from [0, 255] range to [0, 1] range
t_color	convert_color_inverse(t_color color)
{
	t_color	result;

	result.r = convert_component_inverse(color.r);
	result.g = convert_component_inverse(color.g);
	result.b = convert_component_inverse(color.b);
	return (result);
}

/*
int main()
{
	printf("values, %lf, %lf, %lf\n", 0.5, 0.4, 0.1);
	t_color color1 = create_color(0.5, 0.4, 0.1);
	printf("BEFORE: color_1");
	print_color(color1);
	t_color color = convert_color(color1);
	printf("AFTER Converted Color:");
	print_color(color);
	printf("Expected: R: 128 G: 102 B: 26\n");

	printf("***\n\n\n\n***\n");

	t_color	color_255 = create_color(128, 102, 26);
	printf("BEFORE: color_255");
	print_color(color_255);
	t_color	color_1 = convert_color_inverse(color_255);
	printf("AFTER Converted Color:");
	print_color(color_1);
	printf("Expected: R: 0.502 G: 0.400 B: 0.102\n");
	return 0;
 
}
*/
