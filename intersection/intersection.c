/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersection.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftroise <ftroise@student.42roma.it>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 14:50:26 by atucci            #+#    #+#             */
/*   Updated: 2024/09/22 09:48:10 by ftroise          ###   ########.fr       */
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

    // Copia campi semplici
    copy->identifier = ft_strdup(src->identifier); // Assicurati di liberare la memoria con free() in futuro
    copy->center = src->center;
    copy->diameter = src->diameter;
    copy->color = src->color;
    copy->material = src->material;

    // Deep copy della matrice di trasformazione
    copy->transform = malloc_matrix(4, 4);
    if (!copy->transform)
    {
        perror("Failed to allocate memory for matrix");
        free(copy->identifier);  // Libera i dati già allocati
        free(copy);
        exit(EXIT_FAILURE);
    }

    // Copia della matrice di trasformazione 4x4
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

t_intersection	intersection(double t, char *type, void *obj_address, int s)
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
		if(s == 0)
        {
            printf("Create a deep copy of the sphere\n");
			new.obj.address = deep_copy_sphere(sphere);
            printf("s++\n");
            s++;
        }
        else if (s >= 1)
        {
            printf("----------------------------------------------------copia già  effettuata\n\n\n");
	    }
    }
	return (new);
}
