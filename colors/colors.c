/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atucci <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 15:24:32 by atucci            #+#    #+#             */
/*   Updated: 2024/07/30 13:14:04 by atucci           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

// Function to convert color struct to int
int	create_trgb(t_color color)
{
	return (0 << 24 | (int)color.r << 16 | (int)color.g << 8 | (int)color.b);
}
