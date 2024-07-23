/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftroise <ftroise@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 19:22:17 by ftroise           #+#    #+#             */
/*   Updated: 2024/07/23 16:59:40 by ftroise          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

// raycasting/hit.c
t_intersection2* hit(t_intersection2 xs)
{
    t_intersection2* hit_intersection2 = malloc(sizeof(t_intersection2)); // Alloca memoria per la variabile
    if (hit_intersection2 == NULL) {
        // Gestione dell'errore di allocazione della memoria
        return NULL;
    }

    hit_intersection2->count = 0;  // Inizializza il campo count

    int i = 0;
    while (i < xs.count)
    {
        // Verifica se il tempo di intersezione è valido e se è il più vicino
        if (xs.t[i] >= 0 && (hit_intersection2->count == 0 || xs.t[i] < hit_intersection2->t[0]))
        {
            hit_intersection2->count = 1;
            hit_intersection2->t[0] = xs.t[i];
            hit_intersection2->obj_inter[0] = xs.obj_inter[i];
        }
        i++;
    }

    return hit_intersection2;
}

//alex si deve testare ma penso chhe va 

