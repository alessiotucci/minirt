/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_numbers.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atucci <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 17:40:26 by atucci            #+#    #+#             */
/*   Updated: 2025/02/26 09:02:34 by atucci           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

// Helper function to return a default t_color
t_color	default_color(int i)
{
	t_color	color;

	color.r = i;
	color.g = i;
	color.b = i;
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

t_color	parse_color(char *str, t_setting *set)
{
	t_color	color;
	char	**matrix;

	color = default_color(0);
	ft_printf("Parsing color (%s)\n", str);
	matrix = ft_split(str, ',');
	ft_printf("lenght_string_array: [%d]\n", lenght_string_array(matrix));
	if (lenght_string_array(matrix) == 3)
	{
		color.r = ft_atoi(matrix[0]);
		color.g = ft_atoi(matrix[1]);
		color.b = ft_atoi(matrix[2]);
	}
	else
	{
		error_msg("func parse_color:\tmisconfiguration of colors: ");
		ft_printf("%s\n", matrix[lenght_string_array(matrix) - 1]);
		free_struct(set);
		return (free_string_array(matrix), default_color(-42));
	//	exit(-42); I cannot exit here otherwise it will leak
	}
	return (free_string_array(matrix), color);
}

/* difference between tuple and vector,
 * w = 0 for vectors	
 * w = 1 for tuple;*/
t_vector	parse_vector(char *str, double flag, t_setting *set)
{
	t_vector	vector;
	char		**matrix;

	vector = default_vector();
	ft_printf("Parsing vector (%s)\n", str);
	matrix = ft_split(str, ',');
	if (lenght_string_array(matrix) == 3)
	{
		vector.x = my_atof(matrix[0]);
		vector.y = my_atof(matrix[1]);
		vector.z = my_atof(matrix[2]);
		vector.w = flag;
	}
	else
	{
		error_msg("misconfiguation of vectors: ");
		ft_printf("%s\n", matrix[lenght_string_array(matrix) - 1]);
		free_string_array(matrix);
		free_struct(set);
	//	exit(-42); I cannot exit here otherwise it will leak
	}
	return (free_string_array(matrix), print_vector(vector), vector);
}
