/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_numbers.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atucci <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 17:40:26 by atucci            #+#    #+#             */
/*   Updated: 2025/01/24 16:48:31 by atucci           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

// Helper function to return a default t_color
t_color	default_color(void)
{
	t_color	color;

	color.r = 0;
	color.g = 0;
	color.b = 0;
	return (color);
}

// Helper function to return a default t_vector
t_vector	default_vector(void)
{
	t_vector	vector;

	vector.x = 0;
	vector.y = 0;
	vector.z = 0;
	vector.w = 0;
	return (vector);
}

t_color	parse_color(char *str)
{
	t_color	color;
	char	**matrix;

	color = default_color();
	ft_printf("Parsing color (%s)\n", str);
	matrix = ft_split(str, ',');
	if (lenght_string_array(matrix) == 3)
	{
		color.r = ft_atoi(matrix[0]);
		color.g = ft_atoi(matrix[1]);
		color.b = ft_atoi(matrix[2]);
	}
	else
	{
		error_msg("misconfiguration of colors: ");
		ft_printf("%s\n", matrix[lenght_string_array(matrix) - 1]);
	}
	return (free_string_array(matrix), color);
}

/* difference between tuple and vector,
 * w = 0 for vectors	
 * w = 1 for tuple;*/
t_vector	parse_vector(char *str, double flag)
{
	t_vector	vector;
	char	**matrix;

	vector = default_vector();
	ft_printf("Parsing vector (%s)\n", str);
	matrix = ft_split(str, ',');
	if (lenght_string_array(matrix) == 3)
	{
		vector.x = my_atof(matrix[0]);
		vector.y = my_atof(matrix[1]);
		vector.z = my_atof(matrix[2]);
		vector.w = flag;
		//ft_printf("%sFIX THE BUG%s\t", BG_YELLOW, BG_RESET);
	}
	else
	{
		error_msg("misconfiguation of vectors: ");
		ft_printf("%s\n", matrix[lenght_string_array(matrix) - 1]);
	}
	return (free_string_array(matrix), print_vector(vector), vector);

}
