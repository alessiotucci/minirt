/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_shapes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atucci <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/04 16:59:44 by atucci            #+#    #+#             */
/*   Updated: 2025/02/19 15:14:12 by atucci           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

void	start_cylinder(t_setting *set, char **details)
{
	t_cylinder	*new_cylinder;
	double		**def;

	ft_printf("\t%s*SETTING UP CYLINDER*%s\n", GREEN, RESET);
	def = malloc_matrix(4, 4);
	create_identity_matrix(def);
	new_cylinder = malloc(sizeof(t_cylinder));
	if (!new_cylinder)
		return ;
	new_cylinder->identifier = ft_strdup(details[0]);
	new_cylinder->center = parse_vector(details[1], 1.0);
	new_cylinder->axis = parse_vector(details[2], 0.0);
	new_cylinder->diameter = my_atof(details[3]);
	new_cylinder->height = my_atof(details[4]);
	new_cylinder->min = -new_cylinder->height / 2;
	new_cylinder->max = new_cylinder->height / 2;
	new_cylinder->color = parse_color(details[5]);
	new_cylinder->transform = def;
	new_cylinder->material = material(new_cylinder->color);
	add_cylinder_to_array(new_cylinder, set);
}

void	start_spheres(t_setting *set, char **details)
{
	t_sphere	*new_sphere;
	double		**def;

	ft_printf("\n\t%s*SETTING UP SPHERES*%s\n", RED, RESET);
	def = malloc_matrix(4, 4);
	create_identity_matrix(def);
	new_sphere = malloc(sizeof(t_sphere));
	if (!new_sphere)
		return ;
	new_sphere->identifier = ft_strdup(details[0]);
	new_sphere->center = parse_vector(details[1], 1.0);
	new_sphere->diameter = my_atof(details[2]);
	new_sphere->color = parse_color(details[3]);
	new_sphere->transform = def;
	new_sphere->material = material(new_sphere->color);
	add_sphere_to_array(new_sphere, set);
}

void	start_planes(t_setting *set, char **details)
{
	t_plane		*new_plane;
	double		**def;

	ft_printf("\n\t%s*SETTING UP PLANES*%s\n", BLUE, RESET);
	def = malloc_matrix(4, 4);
	create_identity_matrix(def);
	new_plane = malloc(sizeof(t_plane));
	if (!new_plane)
		return ;
	new_plane->identifier = ft_strdup(details[0]);
	new_plane->point = parse_vector(details[1], 1.0);
	new_plane->normal = parse_vector(details[2], 0.0);
	new_plane->color = parse_color(details[3]);
	new_plane->transform = def;
	new_plane->material = material(new_plane->color);
	add_plane_to_array(new_plane, set);
}
