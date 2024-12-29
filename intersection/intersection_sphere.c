/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersection_sphere.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftroise <ftroise@student.42roma.it>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/14 10:04:11 by atucci            #+#    #+#             */
/*   Updated: 2024/12/29 12:24:54 by ftroise          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

/*t_list_intersect *intersect_sphereV2(t_sphere sphere, t_ray old_ray) ORIGINALE
{
	t_vector sphere_to_ray;
	double discriminant;
	double t[2];
	t_list_intersect *list = NULL;
	t_intersection inter1;
	t_intersection inter2;
	t_ray ray;

	double **leaking_matrix;
	double **cp;
	
	cp = copy_matrix(4, 4, sphere.transform);
//	leaking_matrix = inversing_matrix(4, copy_matrix(4, 4, sphere.transform));
	leaking_matrix = inversing_matrix(4, cp);
	//leaking_matrix = inversing_matrix(4, sphere.transform);
	//ray = transform_ray(old_ray, inversing_matrix(4, copy_matrix(4, 4, sphere.transform)));
	ray = transform_ray(old_ray, leaking_matrix);
	free_heap_matrix(leaking_matrix, 4);
	free_heap_matrix(cp, 4);
	sphere_to_ray = get_sphere_to_ray(sphere, ray);
	discriminant = get_discriminant(sphere_to_ray, ray, sphere.diameter / 2.0); // diameter/2 for radius
	if (discriminant < 0)
	{
		// No intersections, return an empty list
		return (NULL);
	}
	t[0] = (-2.0 * dot(sphere_to_ray, ray.direction) - sqrt(discriminant)) / (2.0 * dot(ray.direction, ray.direction));
	t[1] = (-2.0 * dot(sphere_to_ray, ray.direction) + sqrt(discriminant)) / (2.0 * dot(ray.direction, ray.direction));

	inter1 = intersection(t[0], sphere.identifier, &sphere);
	inter2 = intersection(t[1], sphere.identifier, &sphere);
	if (comparing_double(t[0], t[1]))
	{
		add_intersection_l(&list, &inter1);
		return list;
	}
	else
	{
		add_intersection_l(&list, &inter1);
		add_intersection_l(&list, &inter2);
		return list;
	}
}*/

// Funzione aggiornata per gestire l'intersezione con una sfera
t_list_intersect *intersect_sphereV2(t_sphere sphere, t_ray old_ray)
{
    t_vector sphere_to_ray;
    double discriminant;
    double t[2];
    t_list_intersect *list = NULL;
    t_intersection inter1;
    t_intersection inter2;
    t_ray ray;

    double **leaking_matrix;
    double **cp;

    cp = copy_matrix(4, 4, sphere.transform);
    leaking_matrix = inversing_matrix(4, cp);
    ray = transform_ray(old_ray, leaking_matrix);

    free_heap_matrix(leaking_matrix, 4); // NUOVA RIGA: qui liberiamo la matrice invertita per evitare perdite
    free_heap_matrix(cp, 4); // NUOVA RIGA: qui liberiamo la copia della matrice di trasformazione

    sphere_to_ray = get_sphere_to_ray(sphere, ray);
    discriminant = get_discriminant(sphere_to_ray, ray, sphere.diameter / 2.0);

    if (discriminant < 0)
        return (NULL);

    t[0] = (-2.0 * dot(sphere_to_ray, ray.direction) - sqrt(discriminant)) / (2.0 * dot(ray.direction, ray.direction));
    t[1] = (-2.0 * dot(sphere_to_ray, ray.direction) + sqrt(discriminant)) / (2.0 * dot(ray.direction, ray.direction));

    inter1 = intersection(t[0], sphere.identifier, &sphere);
    inter2 = intersection(t[1], sphere.identifier, &sphere);

    if (comparing_double(t[0], t[1]))
    {
        add_intersection_l(&list, &inter1);
    }
    else
    {
        add_intersection_l(&list, &inter1);
        add_intersection_l(&list, &inter2);
    }

    return list; // NUOVA RIGA: qui restituiamo la lista delle intersezioni
}
