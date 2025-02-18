/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersection.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftroise <ftroise@student.42roma.it>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 14:50:26 by atucci            #+#    #+#             */
/*   Updated: 2025/02/18 17:14:51 by atucci           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "../minirt.h"

/* those function are for the deep copy, double check those*/ 
static void copy_simple_fields_sphere(t_sphere *dest, t_sphere *src)
{
	dest->identifier = ft_strdup(src->identifier);
	dest->center = src->center;
	dest->diameter = src->diameter;
	dest->color = src->color;
	dest->material = src->material;
}

static void copy_simple_fields_plane(t_plane *dest, t_plane *src)
{
	dest->identifier = ft_strdup(src->identifier);
	dest->point = src->point;
	dest->color = src->color;
	dest->material = src->material;
	dest->normal = src->normal;
}

//TODO: update this function pls
static void copy_simple_fields_cylinder(t_cylinder *dest, t_cylinder*src)
{
	dest->identifier = ft_strdup(src->identifier);
	dest->center = src->center;
	dest->axis = src->axis;
	dest->height = src->height;
	dest->diameter = src->diameter;
	dest->color = src->color;
}


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

char	*type_to_string(t_type type)
{
	printf("type_to_string: %d\n", type);
	if (type == T_SPHERE)
		return (printf("sphere\n"), "sphere\n");
	if (type == T_PLANE)
		return (printf("plane\n"), "plane\n");
	if (type == T_CYLINDER)
		return (printf("cylinder\n"), "cylinder\n");
	else
		return (printf("not found:[%d]\n", type), "NOT FOUND\n");
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
