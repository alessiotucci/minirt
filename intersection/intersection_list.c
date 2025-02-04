/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersection_list.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atucci <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 16:37:48 by atucci            #+#    #+#             */
/*   Updated: 2025/02/04 13:02:49 by atucci           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

//typedef struct s_intersection_list
//{
//	t_intersection	*intersections;
//	int count;
//}	t_intersection_list;

/*TODO: check if there is code duplication in this function with other list*/

/* 2) this is also needed */
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

/* this is needed */
void	add_intersection(t_intersection_list *l, int index, t_intersection i)
{
	if (index >= 0 && index < l->count)
		l->intersections[index] = i;
}


void	print_intersection(t_intersection i)
{
//	t_sphere		*sphere;

	print_type(i.obj);
	printf("Pointer: %p\n", i.obj.address);
//	sphere = (t_sphere *)i.obj.address; // casting
//	printf("Address of transform: %p\n", sphere->transform);
//	print_single_sphere(sphere);
	//print_int_matrix(4, 4, sphere->transform);
	printf("Value: %f\n", i.t);
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
