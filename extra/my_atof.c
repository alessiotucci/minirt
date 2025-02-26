/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_atof.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atucci <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 15:04:39 by atucci            #+#    #+#             */
/*   Updated: 2024/05/14 21:10:16 by atucci           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"
#include <stdio.h>

static double	process_integer_part(const char *str, int *i)
{
	double	result;

	result = 0.0;
	while (ft_isdigit(str[*i]))
	{
		result = result * 10.0 + (str[*i] - '0');
		(*i)++;
	}
	return (result);
}

static double	process_fractional_part(const char *str, int *i)
{
	double	result;
	double	power;

	result = 0.0;
	power = 1.0;
	if (str[*i] == '.')
	{
		(*i)++;
		while (ft_isdigit(str[*i]))
		{
			result = result * 10.0 + (str[*i] - '0');
			power *= 10.0;
			(*i)++;
		}
	}
	return (result / power);
}

double	my_atof(const char *str)
{
	double	result;
	int		sign;
	int		i;

	i = 0;
	sign = 1;
	while ((str[i]) == ' ')
		i++;
	if (str[i] == '-')
	{
		sign = -1;
		i++;
	}
	else if (str[i] == '+')
		i++;
	result = process_integer_part(str, &i);
	result += process_fractional_part(str, &i);
	return (sign * result);
}
