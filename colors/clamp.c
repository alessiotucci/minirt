/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clamp.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atucci <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 09:40:30 by atucci            #+#    #+#             */
/*   Updated: 2024/07/30 13:16:19 by atucci           ###   ########.fr       */
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
		return (value);
}

