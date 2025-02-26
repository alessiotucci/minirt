/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lighting.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atucci <atucci@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 14:56:06 by atucci            #+#    #+#             */
/*   Updated: 2025/02/19 16:01:06 by atucci           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

t_light	point_light(t_vector pos, t_color c)
{
	t_light	new;

	new.identifier = "TEST";
	new.position = pos;
	new.brightness = 1.0;
	new.color = c;
	return (new);
}
