/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clamp.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atucci <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 09:40:30 by atucci            #+#    #+#             */
/*   Updated: 2025/02/06 19:53:34 by atucci           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

// Helper function to clamp a value within a specified range
double	my_clamp(double value, double min_val, double max_val)
{
	if (value < min_val)
		return (min_val);
	else if (value > max_val)
		return (max_val);
	else
//	(void)min_val;(void)max_val;
		return (value);
}

