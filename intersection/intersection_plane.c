/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersection_plane.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftroise <ftroise@student.42roma.it>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/03 15:26:02 by atucci            #+#    #+#             */
/*   Updated: 2025/02/08 18:05:29 by atucci           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

/*
t_list_intersect	*intersect_plane(t_plane plane, t_ray old_ray)// ORIGINALE
{
	t_ray				ray;
	t_list_intersect	*list;
	t_intersection		inter;(void)inter;
	double				t;
	double				denominator;
	//TODO: LEAK MATRIX
	double **leaking_matrix;
	double **cp;
	
	cp = copy_matrix(4, 4, plane.transform);
	//leaking_matrix = inversing_matrix(4, copy_matrix(4, 4, plane.transform));
	leaking_matrix = inversing_matrix(4, cp);

	list = NULL;
	ray = transform_ray(old_ray, leaking_matrix);
	free_heap_matrix(leaking_matrix, 4);
	free_heap_matrix(cp, 4);
	denominator = dot(plane.normal, ray.direction);
	if (fabs(denominator) < EPSILON_v2)
		return (//printf("PLANE: returning null\n"),// NULL);
	t = dot(subtract(plane.point, ray.origin), plane.normal) / denominator;
	if (t < 0)
		return (//printf("PLANE: returning null\n"),// NULL);
	inter = intersection(t, plane.identifier, &plane);
  //add_intersection_l(&list, &inter);
	return (list);
}
*/

// Funzione aggiornata per gestire l'intersezione con un piano
t_list_intersect *intersect_plane(t_plane plane, t_ray old_ray)
{
    t_ray ray;
    t_list_intersect *list;
    t_intersection inter;
    double t;
    double denominator;

    double **leaking_matrix;
    double **cp;

    cp = copy_matrix(4, 4, plane.transform);
    leaking_matrix = inversing_matrix(4, cp);

    list = NULL;
    ray = transform_ray(old_ray, leaking_matrix);

    free_heap_matrix(leaking_matrix, 4); // NUOVA RIGA: qui liberiamo la matrice invertita per evitare perdite
    free_heap_matrix(cp, 4); // NUOVA RIGA: qui liberiamo la copia della matrice di trasformazione

/*
	printf("DEBUG: intersect_plane: print plane HERE\n");
	print_single_plane(&plane);exit(-42);
*/
    denominator = dot(plane.normal, ray.direction);
    if (fabs(denominator) < EPSILON_v2)
        return (NULL);

    t = dot(subtract(plane.point, ray.origin), plane.normal) / denominator;
    if (t < 0)
        return (NULL);

    inter = intersection(t, plane.identifier, &plane);
    add_intersection_l(&list, &inter);

    return list; // NUOVA RIGA: qui restituiamo la lista delle intersezioni
}
//
