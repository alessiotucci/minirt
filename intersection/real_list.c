/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   real_list.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftroise <ftroise@student.42roma.it>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 10:23:58 by atucci            #+#    #+#             */
/*   Updated: 2024/12/29 14:09:18 by ftroise          ###   ########.fr       */
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

/*void	add_intersection_l(t_list_intersect **head, t_intersection *intersection) //ORIGINALE
{
	t_list_intersect	*new_node;
	t_list_intersect	*current;

	new_node = create_new_node(intersection);
	if (!new_node)
		return (error_msg("malloc failed."));
	if (!*head)
	{
		//printf("The list is %sempty%s, new node the head!\n", GREEN, RESET);
		*head = new_node;
		return ;
	}
	current = *head;
	while (current->next)
		current = current->next;
	current->next = new_node;
}*/

/*
Funzione aggiornata per aggiungere un nodo a una lista con gestione delle eccezioni
I nodi precedenti vengono liberati scorrendo la lista, 
Questo approccio al momento funziona qualcosina toglie ma niente di grosso, ho il dubbio se potra non andare bene quando dovremmo modificare gli oggetti.
*/

void add_intersection_l(t_list_intersect **head, t_intersection *intersection)
{
    t_list_intersect *new_node;
    t_list_intersect *current;

    new_node = create_new_node(intersection);
    if (!new_node)
        return (error_msg("malloc failed."));

    if (!*head)
    {
        *head = new_node; // NUOVA RIGA: qui assegniamo il nuovo nodo come testa della lista perché la lista è vuota
        return;
    }

    current = *head;
    while (current->next)
    {
        t_list_intersect *temp = current; // NUOVA RIGA: teniamo traccia del nodo precedente
        current = current->next;

        free_intersection(temp->intersection); // NUOVA RIGA: liberiamo la memoria del nodo precedente
        free(temp->intersection); 
        free(temp);
    }

    current->next = new_node; 
}

/*
void	free_list(t_list_intersect **head) ORIGINALE
{
	t_list_intersect	*current;
	t_list_intersect	*next_node;

	current = *head;
	while (current)
	{
		next_node = current->next;
		//TODO:free(current->intersection);Free the intersection if it was dynamically allocated
		if (current->intersection)
		{
			free_intersection(current->intersection);
			free(current->intersection);
		}
		free(current);
		current = next_node;
	}
	*head = NULL;
}*/

// Funzione aggiornata per liberare la memoria della lista
void free_list(t_list_intersect **head)
{
    t_list_intersect *current;
    t_list_intersect *next_node;

    current = *head;
    while (current)
    {
        next_node = current->next;

        if (current->intersection)
        {
            free_intersection(current->intersection); // NUOVA RIGA: qui liberiamo le risorse interne dell'intersezione
            free(current->intersection); // NUOVA RIGA: qui liberiamo l'intersezione stessa
        }

        free(current); // NUOVA RIGA: qui liberiamo il nodo della lista
        current = next_node;
    }

    *head = NULL; // NUOVA RIGA: qui resettiamo il puntatore della lista per evitare riferimenti dangling
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
		//TODO; HERE YOU CAN ACCESS
		//	current->intersection;
		if (debug)
			print_intersection(*current->intersection);
		//	current;
		current = next_node;
		count++;
	}
	printf("List count:[%d]\n", count);
}

void	concatenate_lists(t_list_intersect **list1, t_list_intersect *list2)
{
	t_list_intersect	*current;

	if (!*list1)
	{
		*list1 = list2;
		return;
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

