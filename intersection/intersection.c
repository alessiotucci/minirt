/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersection.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atucci <atucci@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 14:50:26 by atucci            #+#    #+#             */
/*   Updated: 2024/07/31 14:50:01 by atucci           ###   ########.fr       */
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
	copy->transform = create_matrix(4, 4);
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			copy->transform[i][j] = src->transform[i][j];
		}
	}

	return copy;
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
		return (T_CAMERA); // THIS IS TO COMPILE
}

t_intersection	intersection(double t, char *type, void *obj_address)
{
	t_intersection	new;
	t_sphere		*sphere;

	//printf("\t\t%sDEBUG LOG: intersection func%s obj_address: %p\n", YELLOW, RESET, obj_address);
	//printf("\t\tintersection value t: %lf\n", t);
	
	new.t = t;
	new.obj.type = string_to_type(type);
	new.obj.address = obj_address;
	if (string_to_type(type) == T_SPHERE)
	{
		sphere = (t_sphere *)obj_address;
		//printf("\t\t%sDEBUG LOG: intersection func%s obj_address->matrix: %p\n", RED, RESET, sphere->transform);
		//print_int_matrix(4, 4, sphere->transform);
		//// Create a deep copy of the sphere
		//printf("Create a deep copy of the sphere\n");
		new.obj.address = deep_copy_sphere(sphere);
	}
	return (new);
}
