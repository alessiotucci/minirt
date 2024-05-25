/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clamp.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atucci <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 09:40:30 by atucci            #+#    #+#             */
/*   Updated: 2024/05/25 09:42:11 by atucci           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

// Helper function to clamp a value within a specified range
int	my_clamp(int value, int min_val, int max_val)
{
	if (value < min_val)
		return (min_val);
	else if (value > max_val)
		return (max_val);
	else
		return (value);
}

