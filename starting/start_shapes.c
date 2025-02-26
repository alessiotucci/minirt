/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_shapes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atucci <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/04 16:59:44 by atucci            #+#    #+#             */
/*   Updated: 2025/02/26 12:15:46 by atucci           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

void	free_set_exit(t_setting *set, int exit_code)
{
	free_struct(set);
	(void)exit_code;
	//exit(exit_code);
}

//1
int	start_cylinder(t_setting *set, char **details)
{
	t_cylinder	*new_cylinder;
	double		**def;
	int			i;

	i = 0;
	ft_printf("\t%s*SETTING UP CYLINDER*%s\n", GREEN, RESET);
	def = malloc_matrix(4, 4);
	create_identity_matrix(def);
	new_cylinder = malloc(sizeof(t_cylinder));
	if (!new_cylinder)
		return (-1);
	if (lenght_string_array(details) != 6)
		return (error_msg("start_cylinder ERROR\n"), free_heap_matrix(def, 4), free(new_cylinder), -1);
	new_cylinder->identifier = ft_strdup(details[0]);
	new_cylinder->center = parse_vector(details[1], 1.0, set);
	new_cylinder->axis = parse_vector(details[2], 0.0, set);
	new_cylinder->diameter = my_atof(details[3]);
	new_cylinder->height = my_atof(details[4]);
	new_cylinder->min = -new_cylinder->height / 2;
	new_cylinder->max = new_cylinder->height / 2;
	new_cylinder->color = parse_color(details[5], set);
	new_cylinder->transform = def;
	new_cylinder->material = material(new_cylinder->color);
	add_cylinder_to_array(new_cylinder, set);
	return (i);
}

//2
int	start_spheres(t_setting *set, char **details)
{
	t_sphere	*new_sphere;
	double		**def;

	ft_printf("\n\t%s*SETTING UP SPHERES*%s\n", RED, RESET);
	def = malloc_matrix(4, 4);
	create_identity_matrix(def);
	new_sphere = malloc(sizeof(t_sphere));
	if (!new_sphere)
		return (-1);
	if (lenght_string_array(details) != 4)
		return (error_msg("start_sphere: misconfig of array\n"), free_heap_matrix(def, 4), free(new_sphere), -1);
	new_sphere->identifier = ft_strdup(details[0]);
	new_sphere->center = parse_vector(details[1], 1.0, set);
	new_sphere->diameter = my_atof(details[2]);
	new_sphere->color = parse_color(details[3], set);
	new_sphere->material = material(new_sphere->color);
	new_sphere->transform = def;
	add_sphere_to_array(new_sphere, set);
	return (0);
}

//TODO: return 
//3
int	start_planes(t_setting *set, char **details)
{
	t_plane		*new_plane;
	double		**def;
	int			i;

	i = 0;
	ft_printf("\n\t%s*SETTING UP PLANES*%s\n", BLUE, RESET);
	def = malloc_matrix(4, 4);
	create_identity_matrix(def);
	new_plane = malloc(sizeof(t_plane));
	if (!new_plane)
		return (-1);
	if (lenght_string_array(details) != 4)
		return (error_msg("func: start_plane, misconfig of array\n"), free_heap_matrix(def, 4), free(new_plane), -1);
	new_plane->identifier = ft_strdup(details[0]);
	new_plane->point = parse_vector(details[1], 1.0, set);
	new_plane->normal = parse_vector(details[2], 0.0, set);
	new_plane->color = parse_color(details[3], set);
	new_plane->transform = def;
	new_plane->material = material(new_plane->color);
	add_plane_to_array(new_plane, set);
	return (i);
}
