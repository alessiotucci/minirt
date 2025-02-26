/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atucci <atucci@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 11:22:13 by atucci            #+#    #+#             */
/*   Updated: 2025/02/26 16:24:20 by atucci           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/* 
 * return 0 == 0k!
 * return 1 == FAIL!
*/
/* Helper function: applies 'func' to each element in 'matrix'.
   Returns OK if all elements pass, otherwise FAIL. */
static int	apply_to_each(char **matrix, int (*func)(char *))
{
	int	i;

	i = 0;
	while (matrix[i])
	{
		if (func(matrix[i]) != OK)
			return (FAIL);
		i++;
	}
	return (OK);
}

/* Check if a character is allowed in a float string */
static int	is_valid_float_char(char c)
{
	return (ft_isdigit(c) || c == '.' || c == '-' || c == '+');
}

/* Validate a single token representing a float.
 Returns OK if token is composed only of valid characters
 and passes valid_for_atof. */
static int	valid_float_token(char *token)
{
	int	i;

	i = 0;
	while (token[i])
	{
		if (!is_valid_float_char(token[i]))
			return (FAIL);
		i++;
	}
	if (valid_for_atof(token) != OK)
		return (FAIL);
	return (OK);
}

/* Validate a single token representing a color component.
   Returns OK if the token represents a valid float
   and its integer conversion is in [0,255]. */
static int	valid_color_component(char *token)
{
	if (valid_for_atof(token) != OK)
		return (FAIL);
	if ((int)my_atof(token) < 0 || (int)my_atof(token) > 255)
		return (FAIL);
	return (OK);
}

/* Validate that 'str' is a valid vector in the format "x,y,z" (floats). */
int	valid_vector(char *str)
{
	char	**matrix;
	int		res;

	matrix = ft_split(str, ',');
	if (!matrix || lenght_string_array(matrix) != 3)
	{
		free_string_array(matrix);
		return (error_msg("VALIDATE VECTOR: need 3 components\n"), FAIL);
	}
	res = apply_to_each(matrix, valid_float_token);
	free_string_array(matrix);
	if (res == OK)
		return (OK);
	return (error_msg("Invalid vector format\n"), FAIL);
}

/* Validate that 'str' is a valid float for conversion.
   Returns OK if the format is acceptable, FAIL otherwise. */
int	valid_for_atof(char *str)
{
	int	i;
	int	has_digit;

	i = 0;
	has_digit = 0;
	while (str[i] == ' ')
		i++;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i])
	{
		if (ft_isdigit(str[i]))
			has_digit = 1;
		else if (str[i] == '.' && ft_isdigit(str[i + 1]))
			;
		else if (str[i] == ' ')
			break ;
		else
			return (error_msg("Invalid float characters\n"), FAIL);
		i++;
	}
	while (str[i] == ' ')
		i++;
	if (has_digit && str[i] == '\0')
		return (OK);
	else
		return (error_msg("Invalid float format\n"), FAIL);
}

/* Validate that 'str' is a valid color string in the format "r,g,b"
 * with each component in [0,255]. */
int	valid_color_string(char *str)
{
	char	**matrix;
	int		res;

	matrix = ft_split(str, ',');
	if (!matrix || lenght_string_array(matrix) != 3)
	{
		free_string_array(matrix);
		return (error_msg("Color needs 3 components\n"), FAIL);
	}
	res = apply_to_each(matrix, valid_color_component);
	free_string_array(matrix);
	if (res == OK)
		return (OK);
	return (error_msg("Invalid color values\n"), FAIL);
}

/* Validate that 'str' represents a valid integer for FOV,
   and that its value is in the range [0,180]. */
int	valid_fov_atoi(char *str)
{
	int	i;
	int	num;

	i = 0;
	num = 0;
	while (str[i] == ' ')
		i++;
	if (str[i] == '-' || str[i] == '+')
		return (error_msg("FOV cannot be negative\n"), FAIL);
	while (str[i] && str[i] != ' ') // this
	{
		if (!ft_isdigit(str[i]))
			return (error_msg("Invalid FOV characters\n"), ft_printf("[%s]", str), FAIL);
		num = num * 10 + (str[i] - '0');
		if (num > 180)
			return (error_msg("FOV exceeds 180\n"), FAIL);
		i++;
	}
	if (num >= 0 && num <= 180)
		return (OK);
	return (error_msg("Invalid FOV range\n"), FAIL);
}

