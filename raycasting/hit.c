/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftroise <ftroise@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 19:22:17 by ftroise           #+#    #+#             */
/*   Updated: 2024/07/22 18:10:40 by ftroise          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

// raycasting/hit.c
t_intersection* hit(t_intersection xs)
{
    t_intersection* hit_intersection = malloc(sizeof(t_intersection)); // Alloca memoria per la variabile
    if (hit_intersection == NULL) {
        // Gestione dell'errore di allocazione della memoria
        return NULL;
    }

    hit_intersection->count = 0;  // Inizializza il campo count

    int i = 0;
    while (i < xs.count)
    {
        // Verifica se il tempo di intersezione è valido e se è il più vicino
        if (xs.t[i] >= 0 && (hit_intersection->count == 0 || xs.t[i] < hit_intersection->t[0]))
        {
            hit_intersection->count = 1;
            hit_intersection->t[0] = xs.t[i];
            hit_intersection->obj_inter[0] = xs.obj_inter[i];
        }
        i++;
    }

    return hit_intersection;
}

//alex si deve testare ma penso chhe va 

