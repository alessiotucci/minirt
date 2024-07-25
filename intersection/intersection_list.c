/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersection_list.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atucci <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 16:37:48 by atucci            #+#    #+#             */
/*   Updated: 2024/07/25 11:28:47 by atucci           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

t_intersection	new_create_intersection(double t, t_type type, void *object)
{
	t_intersection	intersection;
	t_object	temp_obj;

	intersection.t[0] = t; // need to check2
	temp_obj.type = type;
	temp_obj.obj = object;
	intersection.obj = temp_obj;
	return (intersection);
}

/* 1)*/
t_intersection	create_intersection(double t, void *object)
//t_intersection	create_intersection(double t, t_object object)
{
	t_intersection	intersection;

	(void)object;
	intersection.t[0] = t;
	//intersection.obj = object;
	return (intersection);
}


/* 2) */
t_intersection_list	*create_intersection_list(int count)
{
	t_intersection_list	*list;

	list = malloc(sizeof(t_intersection_list));
	if (!list)
		return (NULL);
	list->intersections = malloc(sizeof(t_intersection) * count);
	if (!list->intersections)
		return (free(list), NULL);
	list->count = count;
	return (list);
}

/* 3) */
void	add_intersection(t_intersection_list *l, int index, t_intersection i)
{
	if (index >= 0 && index < l->count)
		l->intersections[index] = i;
}

/* 4) freeing the list of intersection */
void	free_intersection_list(t_intersection_list *list)
{
	if (list)
	{
		if (list->intersections)
			free(list->intersections);
		free(list);
	}
}
