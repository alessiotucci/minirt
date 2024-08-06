/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersection.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atucci <atucci@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 14:50:26 by atucci            #+#    #+#             */
/*   Updated: 2024/08/06 15:55:14 by atucci           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

t_sphere *deep_copy_sphere(t_sphere *src)
{
	t_sphere *copy = malloc(sizeof(t_sphere));
	if (!copy)
	{
		perror("Failed to allocate memory for sphere copy");
		exit(EXIT_FAILURE);
	}

	// Copy simple fields//TODO: create a function to do that
	copy->identifier = ft_strdup(src->identifier);
	copy->center = src->center;
	copy->diameter = src->diameter;
	copy->color = src->color;
	copy->material = src->material;

	// Deep copy the transform matrix//TODO: create a function to do that
	copy->transform = malloc_matrix(4, 4);
	//  358 | double  **copy_matrix(int rows, int cols, double **source);
	copy->transform = copy_matrix(4, 4, src->transform);
	return (copy);
}

t_plane *deep_copy_plane(t_plane *src)
{
	t_plane *copy = malloc(sizeof(t_plane));
	if (!copy)
	{
		perror("Failed to allocate memory for plane copy");
		exit(EXIT_FAILURE);
	}
	// Copy simple fields//TODO: create a function to do that
	copy->identifier = ft_strdup(src->identifier);
	copy->point = src->point;
	copy->normal = src->normal;
	copy->color = src->color;
	//TODO: create a function to do that
	copy->transform = malloc_matrix(4, 4);
	copy->transform = copy_matrix(4, 4, src->transform);
	return (copy);
}

t_type	string_to_type(char *type)
{
	if (my_strcmp(type, "sp") == 0)
		return (T_SPHERE);
	if (my_strcmp(type, "pl") == 0)
		return (T_PLANE);
	if (my_strcmp(type, "cy") == 0)
		return (T_CYLINDER);
	else
		return (T_SPHERE); // THIS IS TO COMPILE
}

#include <stdlib.h>

// Function to free a single intersection
void	free_intersection(t_intersection *intersect)
{
	if (!intersect)
		return ;
	// Check the type of object and free accordingly
	if (intersect->obj.type == T_SPHERE)
	{
		t_sphere *sphere = (t_sphere *)intersect->obj.address;
		free_single_sphere(sphere);
	}
	else if (intersect->obj.type == T_PLANE)
	{
		t_plane *plane = (t_plane *)intersect->obj.address;
		free_single_plane(plane);
	}
	/*
	else if (intersect->obj.type == T_CYLINDER)
	{
		t_cylinder *cylinder = (t_cylinder *)intersect->obj.address;
		free_single_cylinder(cylinder);
	}
	*/
	else
		return ;
}

t_intersection	intersection(double t, char *type, void *obj_address)
{
	t_intersection	new;
	t_sphere		*sphere;
	t_plane			*plane;

	//printf("\t\t%sDEBUG LOG: intersection func%s obj_address: %p\n", YELLOW, RESET, obj_address);
	//printf("\t\tintersection value t: %lf\n", t);
	
	new.t = t;
	//printf("value t: [%lf], string type (%s)\n", t, type);
	new.obj.type = string_to_type(type);
	new.obj.address = obj_address;
	if (string_to_type(type) == T_SPHERE)
	{
		sphere = (t_sphere *)obj_address;
		new.obj.address = deep_copy_sphere(sphere);
	}
	if (string_to_type(type) == T_PLANE)
	{
		plane = (t_plane *)obj_address;
		new.obj.address = deep_copy_plane(plane);
	}
	return (new);
}
