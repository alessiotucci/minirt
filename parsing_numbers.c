/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_numbers.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atucci <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 17:40:26 by atucci            #+#    #+#             */
/*   Updated: 2024/05/05 18:30:52 by atucci           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_color	parse_color(char *str)
{
	t_color	color;
	char	**matrix;
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

t_vector	parse_vector(char *str)
{
	t_vector	vector;
	char	**matrix;
	ft_printf("Parsing vector (%s)\n", str);
	matrix = ft_split(str, ',');
	if (lenght_string_array(matrix) == 3)
	{
		vector.x = ft_atoi(matrix[0]);
		vector.y = ft_atoi(matrix[1]);
		vector.z = ft_atoi(matrix[2]);
	}
	else
	{
		error_msg("misconfiguation of vectors: ");
		ft_printf("%s\n", matrix[lenght_string_array(matrix) - 1]);
	}
	return (free_string_array(matrix), vector);

}
