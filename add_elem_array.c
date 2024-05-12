/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_elem_array.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atucci <atucci@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 21:10:38 by atucci            #+#    #+#             */
/*   Updated: 2024/05/12 11:35:32 by atucci           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/*once we are done allocating memory, we set the index back to zero
 * and then increment each time we add a element to the array */
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
	set->num_spheres++;
}

void	add_cylinder_to_array(t_cylinder *to_add, t_setting *set)
{
	set->cylinders[set->num_cylinders] = to_add;
	set->num_cylinders++;
}

//TODO: this is bonus, now focus on mandatory part
//void	add_cones_to_array(t_light *to_add, t_light **cones)
