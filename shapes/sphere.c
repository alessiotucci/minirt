/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftroise <ftroise@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 19:26:21 by atucci            #+#    #+#             */
/*   Updated: 2025/02/24 17:43:42 by atucci           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

/*
typedef struct s_sphere
{
	char		*identifier;
	t_vector	center;
	double		diameter;
	t_color		color;
}	t_sphere;
*/
int	calculate_sphere_color(t_intersection *intersection)
{
	t_sphere	*sphere;

	sphere = (t_sphere *)intersection->obj.address;
	return (create_trgb(sphere->color));
}
