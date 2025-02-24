/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atucci <atucci@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 16:35:30 by atucci            #+#    #+#             */
/*   Updated: 2025/02/24 16:40:33 by atucci           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

//3
void	default_intersection(t_intersection *i1, t_intersection *i2)
{
	if (i1 != NULL)
	{
		i1->t = 0.0;
		i1->obj.type = T_NULL;
		i1->obj.address = NULL;
	}
	if (i2 != NULL)
	{
		i2->t = 0.0;
		i2->obj.type = T_NULL;
		i2->obj.address = NULL;
	}
}

//2
static int	check_cap_cylinder(t_ray ray, double t)
{
	double	x;
	double	z;

	x = ray.origin.x + t * ray.direction.x;
	z = ray.origin.z + t * ray.direction.z;
	return (pow(x, 2) + (pow(z, 2)) <= 1);
}

//1
// Function to intersect with the caps of the cylinder
void	intersect_caps(t_cylinder cyl, t_ray ray, t_list_intersect **list)
{
	double			t;
	t_intersection	inter1;
	t_intersection	inter2;

	default_intersection(&inter1, &inter2);
	if (!cyl.closed || comparing_double(ray.direction.y, 0.0))
		return ;
	t = (cyl.min - ray.origin.y) / ray.direction.y;
	if (check_cap_cylinder(ray, t))
	{
		inter1 = intersection(t, cyl.identifier, &cyl);
		add_intersection_l(list, &inter1);
	}
	t = (cyl.max - ray.origin.y) / ray.direction.y;
	if (check_cap_cylinder(ray, t))
	{
		inter2 = intersection(t, cyl.identifier, &cyl);
		add_intersection_l(list, &inter2);
	}
}
