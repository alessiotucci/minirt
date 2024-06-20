/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftroise <ftroise@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 19:22:17 by ftroise           #+#    #+#             */
/*   Updated: 2024/06/20 05:45:23 by ftroise          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

t_intersection2* hit(t_intersection xs)
{
    t_intersection2* hit_intersection = NULL;
    int i = 0;

    while (i < xs.count)
    {
        int j = 0;
        while (j < xs.intersections[i].count)
        {
            if (xs.intersections[i].t[j] >= 0 && (hit_intersection == NULL || xs.intersections[i].t[j] < hit_intersection->t[0]))
            {
                hit_intersection = &xs.intersections[i];
                hit_intersection->count = 1;
                hit_intersection->t[0] = xs.intersections[i].t[j];
                hit_intersection->obj_inter[0] = xs.intersections[i].obj_inter[j];
            }
            j++;
        }
        i++;
    }

    return hit_intersection;
}
//alex si deve testare ma penso chhe va 

