/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersection.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftroise <ftroise@student.42roma.it>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 14:50:26 by atucci            #+#    #+#             */
/*   Updated: 2025/02/19 15:56:37 by atucci           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "../minirt.h"

t_sphere	*deep_copy_sphere(t_sphere *src)
{
	t_sphere	*copy;

	copy = malloc(sizeof(t_sphere));
	if (!copy)
	{
		perror("Failed to allocate memory for sphere copy");
		exit(EXIT_FAILURE);
	}
	copy_simple_fields_sphere(copy, src);
	copy->transform = copy_matrix(4, 4, src->transform);
	return (copy);
}

t_plane	*deep_copy_plane(t_plane *src)
{
	t_plane	*copy;

	copy = malloc(sizeof(t_plane));
	if (!copy)
	{
		perror("Failed to allocate memory for plane copy");
		exit(EXIT_FAILURE);
	}
	copy_simple_fields_plane(copy, src);
	copy->transform = copy_matrix(4, 4, src->transform);
	return (copy);
}

t_cylinder	*deep_copy_cylinder(t_cylinder *src)
{
	t_cylinder	*copy;

	copy = malloc(sizeof(t_cylinder));
	if (!copy)
	{
		perror("Failed to allocate memory for cylinder copy");
		exit(EXIT_FAILURE);
	}
	copy_simple_fields_cylinder(copy, src);
	copy->transform = copy_matrix(4, 4, src->transform);
	return (copy);
}

//2 Function to free a single intersection
void	free_intersection(t_intersection *intersect)
{
	if (!intersect)
		return (error_msg("F: free_intersection!\n"));
	if (intersect->obj.type == T_SPHERE)
		free_single_sphere((t_sphere *)intersect->obj.address);
	else if (intersect->obj.type == T_PLANE)
		free_single_plane((t_plane *)intersect->obj.address);
	else if (intersect->obj.type == T_CYLINDER)
		free_single_cylinder((t_cylinder *)intersect->obj.address);
	else
		return (error_msg("F: free_intersection! obj not FOUND\n"));
}

//1
t_intersection	intersection(double t, char *type, void *obj_address)
{
	t_intersection	new;

	new.t = t;
	new.obj.type = string_to_type(type);
	new.obj.original_addr = obj_address;
	if (string_to_type(type) == T_SPHERE)
		new.obj.address = deep_copy_sphere((t_sphere *)obj_address);
	if (string_to_type(type) == T_PLANE)
		new.obj.address = deep_copy_plane((t_plane *)obj_address);
	if (string_to_type(type) == T_CYLINDER)
		new.obj.address = deep_copy_cylinder((t_cylinder *)obj_address);
	return (new);
}
