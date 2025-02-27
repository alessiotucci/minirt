/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_intersection.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atucci <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/29 15:14:44 by atucci            #+#    #+#             */
/*   Updated: 2025/02/27 16:51:20 by atucci           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

void	insert_sorted(t_list_intersect **sorted, t_list_intersect *new)
{
	t_list_intersect	*current;

	// Null guard: ensure new node and its intersection exist
	if (!new || !new->intersection)
		return ;

	// Handle empty list or insert at head
	if (*sorted == NULL || ((*sorted)->intersection && (*sorted)->intersection->t > new->intersection->t))
	{
		new->next = *sorted;
		*sorted = new;
	}
	else
	{
		current = *sorted;
		// Traverse while checking for valid intersections
		while (current->next && current->next->intersection &&
			current->next->intersection->t < new->intersection->t)
		{
			current = current->next;
		}
		new->next = current->next;
		current->next = new;
	}
}

void	sort_intersection_list(t_list_intersect **head)
{
	t_list_intersect	*sorted_list;
	t_list_intersect	*current;
	t_list_intersect	*next_node;

	if (!head || !*head) // Null-check input
		return ;

	sorted_list = NULL;
	current = *head;
	while (current)
	{
		next_node = current->next;
		current->next = NULL; // Detach node before insertion
		insert_sorted(&sorted_list, current);
		current = next_node;
	}
	*head = sorted_list;
}
