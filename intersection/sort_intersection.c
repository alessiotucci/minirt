/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_intersection.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atucci <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/29 15:14:44 by atucci            #+#    #+#             */
/*   Updated: 2024/09/29 15:17:58 by atucci           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

void	insert_sorted(t_list_intersect **sorted, t_list_intersect *new)
{
	if (*sorted == NULL || (*sorted)->intersection->t > new->intersection->t)
	{
		new->next = *sorted;
		*sorted = new;
	}
	else
	{
		t_list_intersect *current = *sorted;
		while (current->next != NULL && current->next->intersection->t < new->intersection->t)
			current = current->next;

		new->next = current->next;
		current->next = new;
	}
}

void	sort_intersection_list(t_list_intersect **head)
{
	t_list_intersect	*sorted_list;
	t_list_intersect	*current;
	t_list_intersect	*next_node;

	sorted_list = NULL;
	current = *head;
	while (current != NULL)
	{
		next_node = current->next;
		insert_sorted(&sorted_list, current);
		current = next_node;
	}
	*head = sorted_list;
}

