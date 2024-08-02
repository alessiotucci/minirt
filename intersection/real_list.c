/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   real_list.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atucci <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 10:23:58 by atucci            #+#    #+#             */
/*   Updated: 2024/08/02 10:43:06 by atucci           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

t_list_intersect	*create_new_node(t_intersection *intersection)
{
	t_list_intersect	*new_node;

	new_node = (t_list_intersect *)malloc(sizeof(t_list_intersect));
	if (!new_node)
		return (error_msg("malloc failed."), NULL);
	new_node->intersection = intersection;
	new_node->next = NULL;
	return (new_node);
}

void	add_intersection_l(t_list_intersect **head, t_intersection *intersection)
{
	t_list_intersect	*new_node;
	t_list_intersect	*current;

	new_node = create_new_node(intersection);
	if (!new_node)
		return (error_msg("malloc failed."));
	if (!*head)
	{
		printf("The list is %sempty%s, new node the head!\n", GREEN, RESET);
		*head = new_node;
		return ;
	}
	current = *head;
	while (current->next)
		current = current->next;
	current->next = new_node;
}

void	free_list(t_list_intersect **head)
{
	t_list_intersect	*current;
	t_list_intersect	*next_node;

	current = *head;
	while (current)
	{
		next_node = current->next;
		//TODO:free(current->intersection);Free the intersection if it was dynamically allocated
		free(current);
		current = next_node;
	}
	*head = NULL;
}

void	print_list(t_list_intersect **head)
{
	t_list_intersect	*current;
	t_list_intersect	*next_node;

	current = *head;
	while (current)
	{
		next_node = current->next;
		//TODO; HERE YOU CAN ACCESS
		//	current->intersection;
		print_intersection(*current->intersection);
		//	current;
		current = next_node;
	}
	*head = NULL;
}
