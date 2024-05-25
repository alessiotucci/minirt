/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atucci <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 15:24:32 by atucci            #+#    #+#             */
/*   Updated: 2024/05/23 15:25:57 by atucci           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

// Function to convert color struct to int
int	create_trgb(t_color color)
{
	return (0 << 24 | color.r << 16 | color.g << 8 | color.b);
}
