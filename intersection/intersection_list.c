/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   real_list.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftroise <ftroise@student.42roma.it>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 10:23:58 by atucci            #+#    #+#             */
/*   Updated: 2025/02/19 15:36:44 by atucci           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

t_list_intersect	*create_new_node(t_intersection *intersection)
{
	t_list_intersect	*new_node;

	new_node = (t_list_intersect *)malloc(sizeof(t_list_intersect));
	if (!new_node)
		return (error_msg("malloc failed."), NULL);
	new_node->intersection = (t_intersection *)malloc(sizeof(t_intersection));
	if (!new_node->intersection)
		return (free(new_node), error_msg("malloc failed."), NULL);
	*(new_node->intersection) = *intersection;
	new_node->next = NULL;
	return (new_node);
}

void	add_intersection_l(t_list_intersect **head, t_intersection *inter)
{
	t_list_intersect	*new_node;
	t_list_intersect	*current;
	t_list_intersect	*temp;

	new_node = create_new_node(inter);
	if (!new_node)
		return (error_msg("malloc failed."));
	if (!*head)
	{
		*head = new_node;
		return ;
	}
	current = *head;
	while (current->next)
	{
		temp = current;
		current = current->next;
		free_intersection(temp->intersection);
		free(temp->intersection);
		free(temp);
	}
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
		if (current->intersection)
		{
			free_intersection(current->intersection);
			free(current->intersection);
		}
		free(current);
		current = next_node;
	}
	*head = NULL;
}

void	print_list(t_list_intersect **head, int debug)
{
	t_list_intersect	*current;
	t_list_intersect	*next_node;
	int					count;

	count = 0;
	current = *head;
	while (current)
	{
		next_node = current->next;
		if (debug)
			print_intersection(*current->intersection);
		current = next_node;
		count++;
	}
	if (count > 0)
		printf("List count:[%d]\n", count);
	else
		return ;
}

void	concatenate_lists(t_list_intersect **list1, t_list_intersect *list2)
{
	t_list_intersect	*current;

	if (!*list1)
	{
		*list1 = list2;
		return ;
	}
	current = *list1;
	while (current->next)
		current = current->next;
	current->next = list2;
}

/*
int	main()
{
	printf("%sTEST:%s aggregating intersections\n", RED, RESET);
	t_color bogus;
	bogus.r = 0; bogus.g = 0; bogus.b = 0;

	t_vector p = create_point(0, 0, 0);

	t_sphere s = create_sphere("sp", p, 1.0, bogus); // create unit sphere (s)
	t_sphere s1 = create_sphere("sp", p, 2.5, bogus); // create unit sphere (s)

	// created a ray1 here
	t_vector origin1 = create_point(0, 0, -5);
	t_vector direction1 = create_vector(0, 0, 1);
	t_ray ray1 = create_ray(origin1, direction1);
	// created a ray2 here
	t_vector origin2 = create_point(0, 0, -5);
	t_vector direction2 = create_vector(0, 0, 1);
	t_ray ray2 = create_ray(origin2, direction2);

	t_list_intersect *first = intersect_sphereV2(s, ray1);
	t_list_intersect *second = intersect_sphereV2(s1, ray2);
	printf("\nfirst_list\n");
	// then print out the list
	print_list(&first, 0);

	printf("\nsecond_list\n");
	// then print out the list
	print_list(&second, 0);
	 // Concatenate the lists
	concatenate_lists(&first, second);

	printf("\nconcatenated_list\n");
	print_list(&first, 0);
	// Free the list
	free_list(&first);

	//free since those sphere are not malloced
	free_heap_matrix(s.transform, 4);
	free_heap_matrix(s1.transform, 4);

	return (0);
}
*/
