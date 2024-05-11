/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_shapes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atucci <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/04 16:59:44 by atucci            #+#    #+#             */
/*   Updated: 2024/05/11 12:40:43 by atucci           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	start_cylinder(t_setting *set, char **details)
{
	ft_printf("setting up cylinder\n");
	(void)set;
	t_cylinder	new_cylinder;
	(void)new_cylinder;
	new_cylinder.identifier = ft_strdup(details[0]);
	new_cylinder.center = parse_vector(details[1]);
	new_cylinder.axis = parse_vector(details[2]); //TODO carefull with ranges
	new_cylinder.diameter = atof(details[3]);
	new_cylinder.height = atof(details[4]);
	new_cylinder.color = parse_color(details[5]);
	//TODO: write this function
	add_cylinder_to_array(&new_cylinder, set);

}

void	start_spheres(t_setting *set, char **details)
{
	ft_printf("setting up spheres\n");
	(void)set;
	t_sphere	new_sphere;
	(void)new_sphere;
	new_sphere.identifier = ft_strdup(details[0]);
	new_sphere.center = parse_vector(details[1]);
	new_sphere.diameter = atof(details[2]); //TODO: implement my own
	new_sphere.color = parse_color(details[3]);
	ft_printf("debug!\n");
	print_color(new_sphere.color);
	//TODO: write this function
	add_sphere_to_array(&new_sphere, set);

}

void	start_planes(t_setting *set, char **details)
{
	ft_printf("setting up planes\n");
	(void)set;
	t_plane	new_plane;
	(void)new_plane;
	new_plane.identifier = ft_strdup(details[0]);
	new_plane.point = parse_vector(details[1]);
	new_plane.normal = parse_vector(details[2]); //TODO: Carefull with ranges
	new_plane.color = parse_color(details[3]);
	//TODO: write this function
	add_plane_to_array(&new_plane, set);

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
