/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftroise <ftroise@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 19:22:17 by ftroise           #+#    #+#             */
/*   Updated: 2025/02/06 18:33:32 by atucci           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"


t_intersection	*hit_v2(t_list_intersect *list)
{
	t_intersection	*closest_hit;
	t_list_intersect	*current;

	closest_hit = NULL;
	current = list;
	while (current)
	{
		if (current->intersection->t >= 0 &&
			(closest_hit == NULL || current->intersection->t < closest_hit->t))
			closest_hit = current->intersection;
		current = current->next;
	}
	return (closest_hit);
}


/*
t_intersection	*hit(t_intersection_list *list)
{
	t_intersection	*closest_hit;
	int				i;

	closest_hit = NULL;
	i = 0;
	while (i < list->count)
	{
		if (list->intersections[i].t >= 0 &&
			(closest_hit == NULL || list->intersections[i].t < closest_hit->t))
		{
			closest_hit = &list->intersections[i];
		}
		i++;
	}
	return (closest_hit);
}
*/

/*
int	main()
{
	t_color bogus;
	bogus.r = 0; bogus.g = 0; bogus.b = 0;
	t_vector p = create_point(0, 0, 0);
	t_sphere a = create_sphere("sp", p, 1.0, bogus); // create unit sphere

	printf("%sTEST 1%s\n", RED, RESET);
	t_intersection a1 = intersection(1.0, a.identifier, &a);
	t_intersection a2 = intersection(2.0, a.identifier, &a);
	t_intersection_list *list1 = create_intersection_list(2);
	list1->count = 2;
	add_intersection(list1, 0, a1);
	add_intersection(list1, 1, a2);
	t_intersection *result1 = hit(list1);
	if (result1 != NULL)
	print_intersection(*result1);

	printf("%sTEST 2%s\n", RED, RESET);
	t_intersection b1 = intersection(-1.0, a.identifier, &a);
	t_intersection b2 = intersection(1.0, a.identifier, &a);
	t_intersection_list *list2 = create_intersection_list(2);
	list2->count = 2;
	add_intersection(list2, 0, b1);
	add_intersection(list2, 1, b2);
	t_intersection *result2 = hit(list2);
	if (result2 != NULL)
		print_intersection(*result2);

	printf("%sTEST 3%s\n", RED, RESET);
	t_intersection c1 = intersection(-2.0, a.identifier, &a);
	t_intersection c2 = intersection(-1.0, a.identifier, &a);
	t_intersection_list *list3 = create_intersection_list(2);
	list3->count = 2;
	add_intersection(list3, 0, c1);
	add_intersection(list3, 1, c2);
	t_intersection *result3 = hit(list3);
	if (result3 != NULL)
		print_intersection(*result3);


	printf("%sTEST 4%s\n", RED, RESET);
	t_intersection d1 = intersection(5.0, a.identifier, &a);
	t_intersection d2 = intersection(7.0, a.identifier, &a);
	t_intersection d3 = intersection(-3.0, a.identifier, &a);
	t_intersection d4 = intersection(2.0, a.identifier, &a);
	t_intersection_list *list4 = create_intersection_list(4);
	list4->count = 4;
	add_intersection(list4, 0, d1);
	add_intersection(list4, 1, d2);
	add_intersection(list4, 2, d3);
	add_intersection(list4, 3, d4);
	t_intersection *result4 = hit(list4);
	if (result4 != NULL)
	print_intersection(*result4);

}
*/
