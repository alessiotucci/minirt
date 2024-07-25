/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersection_list.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atucci <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 16:37:48 by atucci            #+#    #+#             */
/*   Updated: 2024/07/25 12:51:09 by atucci           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

/*typedef struct s_intersection_list
{
	t_intersection	*intersections;
	int count;
}	t_intersection_list;
*/
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

/* 1) this function need to be checked, because it has issues*/
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

void	print_intersection(t_intersection i)
{
	//TODO later to add the print of the obj
	print_type(i.obj);
	if (i.count != 0)
	{
		printf("values[0]: %f\n", i.t[0]);
		if (i.count > 1)
			printf("values[1]: %f\n", i.t[1]);
	}
	else
		printf("no hits\n");
}

void	print_intersection_list(t_intersection_list *lis)
{
	int	count;

	printf("\n\t%sLIST OF INTERSECTION!%s\n", GREEN, RESET);
	count = 0;
	while (count < lis->count)
	{
		printf("\n\t* * index list: %d * *\n", count);
		print_intersection(lis->intersections[count]);
		printf("\t* * *\n");
		count++;
	}
}
//HOW TO COMPILE IT?
t_intersection	intersect_sphere(t_sphere sphere, t_ray ray);
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
// gcc ../matrix/*.c ../vector/*.c   ../extra/comparing.c ../extra/print_debug.c ../shapes/sphere.c  ../libft/libft.a ../raycasting/intersection_ray.c ../raycasting/create_ray.c  ../raycasting/utils_obj.c  intersection_list.c -lm


