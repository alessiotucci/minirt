/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation_extra.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atucci <atucci@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 13:12:26 by atucci            #+#    #+#             */
/*   Updated: 2025/02/27 13:30:32 by atucci           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/**
 * valid_normal_vector
 * Assumes that 'str' is a valid vector in the format "x,y,z" (floats)
 * This function checks that the vector is normalized 
 */
int	valid_normal_vector(char *str)
{
	char	**matrix;
	double	x;
	double	y;
	double	z;
	double	magnitude;

	matrix = ft_split(str, ',');
	if (!matrix || lenght_string_array(matrix) != 3)
		return (free_string_array(matrix), error_msg("UNEXPECTED\n"), FAIL);
	x = my_atof(matrix[0]);
	y = my_atof(matrix[1]);
	z = my_atof(matrix[2]);
	free_string_array(matrix);
	magnitude = sqrt(x * x + y * y + z * z);
	if (fabs(magnitude - 1.0) > 0.001)
		return (error_msg("valid_normal_vector not normalized\n"), FAIL);
	return (OK);
}

/**
 * valid_fov
 *
 * Checks that the given string represents a valid field-of-view (FOV) value.
 * The string must represent a valid float (using valid_for_atof) and its value
 * must be greater than 0 and less than or equal to 180.
 *
 * Returns OK if the FOV is valid, otherwise returns FAIL.
 */
int	valid_fov(char *str)
{
	double	value;

	if (valid_for_atof(str) != OK)
		return (FAIL);
	value = my_atof(str);
	if (value <= 0 || value > 180)
		return (error_msg("valid_fov: FOV must be > 0 and <= 180\n"), FAIL);
	return (OK);
}

/**
 * valid_ratio
 *
 * Checks that the given string represents a valid ratio.
 * The string must represent a valid float (using valid_for_atof) and its value
 * must be between 0 and 1 inclusive.
 *
 * Returns OK if the ratio is valid, otherwise returns FAIL.
 */
int	valid_ratio(char *str)
{
	double	value;

	printf("valid_ratio\n");
	if (valid_for_atof(str) != OK)
		return (FAIL);
	value = my_atof(str);
	if (value < 0.0 || value > 1.0)
		return (error_msg("valid_ratio: Ratio must be between 0 - 1\n"), FAIL);
	return (OK);
}
