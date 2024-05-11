/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_elem_array.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atucci <atucci@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 21:10:38 by atucci            #+#    #+#             */
/*   Updated: 2024/05/11 12:49:13 by atucci           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	add_light_to_array(t_light *to_add, t_setting *set)
{
	set->lights[set->num_lights] = to_add;
	set->num_lights++;
}

void	add_plane_to_array(t_plane *to_add, t_setting *set)
{
	set->planes[set->num_planes] = to_add;
	set->num_planes++;
}

void	add_sphere_to_array(t_sphere *to_add, t_setting *set)
{
	set->spheres[set->num_spheres] = to_add;
	print_color(set->spheres[set->num_spheres]->color);
	set->num_spheres++;
}

void	add_cylinder_to_array(t_cylinder *to_add, t_setting *set)
{
	set->cylinders[set->num_cylinders] = to_add;
	set->num_cylinders++;
}

//TODO: this is bonus, now focus on mandatory part
//void	add_cones_to_array(t_light *to_add, t_light **cones)
