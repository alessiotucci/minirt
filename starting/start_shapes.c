/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_shapes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atucci <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/04 16:59:44 by atucci            #+#    #+#             */
/*   Updated: 2024/07/26 10:46:37 by atucci           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

void	start_cylinder(t_setting *set, char **details)
{
	ft_printf("\t%s*SETTING UP CYLINDER*%s\n", GREEN, RESET);
	t_cylinder	*new_cylinder;
	new_cylinder = malloc(sizeof(t_cylinder));;
	if (!new_cylinder)
		return ;//TODO add the check
	new_cylinder->identifier = ft_strdup(details[0]);
	new_cylinder->center = parse_vector(details[1], 1.0);
	new_cylinder->axis = parse_vector(details[2], 0.0); //TODO carefull with ranges
	new_cylinder->diameter = atof(details[3]);
	new_cylinder->height = atof(details[4]);
	new_cylinder->color = parse_color(details[5]);
	add_cylinder_to_array(new_cylinder, set);

}

void	start_spheres(t_setting *set, char **details)
{
	ft_printf("\n\t%s*SETTING UP SPHERES*%s\n", RED, RESET);
	t_sphere	*new_sphere;
	double		**def;

	def = create_matrix(4, 4);
	create_identity_matrix(def);
	new_sphere = malloc(sizeof(t_sphere));;
	if (!new_sphere)
		return ;//TODO add the check
	new_sphere->identifier = ft_strdup(details[0]);
	new_sphere->center = parse_vector(details[1], 1.0);
	new_sphere->diameter = my_atof(details[2]);
	new_sphere->color = parse_color(details[3]);
	new_sphere->transform = def;//TODO: this is last
	add_sphere_to_array(new_sphere, set);

}

void	start_planes(t_setting *set, char **details)
{
	ft_printf("\n\t%s*SETTING UP PLANES*%s\n", BLUE, RESET);
	t_plane	*new_plane;
	new_plane = malloc(sizeof(t_plane));;
	if (!new_plane)
		return ;//TODO add the check
	new_plane->identifier = ft_strdup(details[0]);
	new_plane->point = parse_vector(details[1], 1.0);
	new_plane->normal = parse_vector(details[2], 0.0); //TODO: Carefull with ranges
	new_plane->color = parse_color(details[3]);
	add_plane_to_array(new_plane, set);

}

void	start_cones(t_setting *set, char **details)
{
	(void)set;
	(void)details;

}
/* focus on mandatory for now */
/*
void	start_cones(t_setting *set, char **details)
{
	ft_printf("setting up cones\n");
	(void)set;
	t_cone	new_cone;
	(void)new_cone;
	new_cone.identifier = ft_strdup(details[0]);
	new_cone.position = parse_vector(details[1]);
	new_cone.brightness = atof(details[2]); //TODO: implement my own
	new_cone.color = parse_color(details[3]);
	//TODO: write this function
	// add_cone_to_array(set, set->cone);

}*/
