/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersection.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atucci <atucci@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 14:50:26 by atucci            #+#    #+#             */
/*   Updated: 2024/12/23 17:14:13 by atucci           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
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
	//copy->transform = malloc_matrix(4, 4);
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
	//copy->transform = malloc_matrix(4, 4);
	copy->transform = copy_matrix(4, 4, src->transform);
	return (copy);
}

t_cylinder	*deep_copy_cylinder(t_cylinder *src)
{
	t_cylinder *copy = malloc(sizeof(t_cylinder));
	if (!copy)
	{
		perror("Failed to allocate memory for cylinder copy");
		exit(EXIT_FAILURE);
	}
	// Copy simple fields//TODO: create a function to do that
	copy->identifier = ft_strdup(src->identifier);
	copy->center = src->center;
	copy->axis = src->axis;
	copy->height = src->height;
	copy->diameter = src->diameter;
	copy->color = src->color;
	//TODO: create a function to do that
	//copy->transform = malloc_matrix(4, 4);
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
	{
		printf("Verbose Log: string to type failed, check the string of the obj...\n");
		exit(-42);
	}
		//return (T_SPHERE); // THIS IS TO COMPILE
}


// Function to free a single intersection
void	free_intersection(t_intersection *intersect)
{
	if (!intersect)
		return (error_msg("F: free_intersection!\n"));
	// Check the type of object and free accordingly
	if (intersect->obj.type == T_SPHERE)
		free_single_sphere((t_sphere *)intersect->obj.address);
	else if (intersect->obj.type == T_PLANE)
		free_single_plane((t_plane *)intersect->obj.address);
	else if (intersect->obj.type == T_CYLINDER)
		free_single_cylinder((t_cylinder *)intersect->obj.address);
	else
		return (error_msg("F: free_intersection! obj not FOUND\n"));
}

t_intersection	intersection(double t, char *type, void *obj_address)
{
	t_intersection	new;


	//printf("\t\t%sDEBUG LOG: intersection func%s obj_address: %p\n", YELLOW, RESET, obj_address);
	//printf("\t\tintersection value t: %lf\n", t);
	
	new.t = t;
	new.obj.type = string_to_type(type);
	new.obj.address = obj_address;
	//printf("value t: [%lf], string type (%s)\n", t, type);
	if (string_to_type(type) == T_SPHERE)
		new.obj.address = deep_copy_sphere((t_sphere *)obj_address);
	if (string_to_type(type) == T_PLANE)
		new.obj.address = deep_copy_plane((t_plane *)obj_address);
	if (string_to_type(type) == T_CYLINDER)
		new.obj.address = deep_copy_cylinder((t_cylinder *)obj_address);
	return (new);
}
