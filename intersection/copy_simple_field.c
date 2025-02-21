/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   copy_simple_field.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atucci <atucci@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 15:52:03 by atucci            #+#    #+#             */
/*   Updated: 2025/02/19 15:55:15 by atucci           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

/* those function are for the deep copy, double check those*/
void	copy_simple_fields_sphere(t_sphere *dest, t_sphere *src)
{
	dest->identifier = ft_strdup(src->identifier);
	dest->center = src->center;
	dest->diameter = src->diameter;
	dest->color = src->color;
	dest->material = src->material;
}

void	copy_simple_fields_plane(t_plane *dest, t_plane *src)
{
	dest->identifier = ft_strdup(src->identifier);
	dest->point = src->point;
	dest->color = src->color;
	dest->material = src->material;
	dest->normal = src->normal;
}

//TODO: update this function pls
void	copy_simple_fields_cylinder(t_cylinder *dest, t_cylinder*src)
{
	dest->identifier = ft_strdup(src->identifier);
	dest->center = src->center;
	dest->axis = src->axis;
	dest->height = src->height;
	dest->diameter = src->diameter;
	dest->color = src->color;
}
