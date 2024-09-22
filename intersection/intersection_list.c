/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersection_list.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftroise <ftroise@student.42roma.it>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 16:37:48 by atucci            #+#    #+#             */
/*   Updated: 2024/09/22 09:49:55 by ftroise          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

//typedef struct s_intersection_list
//{
//	t_intersection	*intersections;
//	int count;
//}	t_intersection_list;

//TODO: GPT gave this to me
void	add_intersections_to_list(t_intersection_list *dest, t_intersection_list *src)
{
	for (int i = 0; i < src->count; i++)
	{
		if (dest->count < src->count)
		{
			dest->intersections[dest->count] = src->intersections[i];
			dest->count++;
		}
	}
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
void free_sphere(t_sphere *sphere) {
    if (!sphere) return;

    // Libera la matrice di trasformazione
    if (sphere->transform)
	{
        free_heap_matrix(sphere->transform, 4); // Supponendo che la matrice sia 4x4
    }

    // Libera l'identificatore se è stato allocato dinamicamente
    if (sphere->identifier) {
        free(sphere->identifier);
    }

    // Libera la struttura sfera
    free(sphere);
}

static void free_intersection(t_intersection *inter) {
    if (inter->obj.type == T_SPHERE) {
        // Libera la copia profonda della sfera
        free_sphere((t_sphere *)inter->obj.address);
    }
    // Se ci sono altri tipi di oggetti, aggiungili qui
}


/* 4) freeing the list of intersection */
void free_intersection_list(t_intersection_list *list) {
    if (list == NULL)
        return;

    for (int i = 0; i < list->count; i++) {
        // Stampa le informazioni dell'intersezione per il debug
        print_intersection_data(&list->intersections[i]);

        // Libera ogni singola intersezione
        free_intersection(&list->intersections[i]);
    }

    free(list->intersections); // Libera l'array di intersezioni
    free(list); // Libera la lista stessa
}

void	print_intersection(t_intersection i)
{
	t_sphere		*sphere;

	print_type(i.obj);
	printf("Pointer: %p\n", i.obj.address);
	sphere = (t_sphere *)i.obj.address; // casting
	printf("Address of transform: %p\n", sphere->transform);
	print_single_sphere(sphere);
	//print_int_matrix(4, 4, sphere->transform);
	printf("Value: %f\n", i.t);
}

void	print_intersection_list(t_intersection_list *lis)
{
	int	count;

	printf("\n\t%sLIST OF INTERSECTION!%s\n", GREEN, RESET);
	printf("intersection.count: [%d]\n", lis->count);
	count = 0;
	while (count < lis->count)
	{
		printf("\n\t* * index list: %d * *\n", count);
		print_intersection(lis->intersections[count]);
		printf("\t* * *\n");
		count++;
	}
}

/* main to test out the functionality */
	/*
int	main()
{
	printf("%sTEST:%s aggregating intersections\n", RED, RESET);
	t_color	bogus;
	bogus.r = 0; bogus.g = 0; bogus.b = 0;

	t_vector p = create_point(0, 0, 0);

	t_sphere s = create_sphere("S", p, 1.0, bogus); // create unit sphere (s)

	// created a ray1 here
	t_vector origin1 = create_point(0, 0, -5);
	t_vector direction1 = create_vector(0, 0, 1);
	t_ray ray1 = create_ray(origin1, direction1);
	// created a ray2 here
	t_vector origin2 = create_point(0, 0, -5);
	t_vector direction2 = create_vector(0, 0, 1);
	t_ray ray2 = create_ray(origin2, direction2);

	t_intersection first = intersect_sphere(s, ray1);
	t_intersection second = intersect_sphere(s, ray2);
	// intersection list created
	t_intersection_list *new_list = create_intersection_list(2);
	// add the intersection to the list, with index and stuff
	add_intersection(new_list, 0, first);
	add_intersection(new_list, 1, second);
	// then print out the list
	print_intersection_list(new_list);

	return (0);
}
	*/
// gcc ../matrix/*.c ../vector/*.c   ../extra/comparing.c ../extra/print_debug.c ../shapes/sphere.c  ../libft/libft.a ../raycasting/intersection_ray.c ../raycasting/create_ray.c  ../raycasting/utils_obj.c  intersection_list.c -lm
