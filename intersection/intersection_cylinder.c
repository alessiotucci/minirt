/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersection_cylinder.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atucci <atucci@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 13:27:39 by atucci            #+#    #+#             */
/*   Updated: 2024/12/13 14:09:54 by atucci           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"


t_list_intersect	*intersect_cylinder(t_cylinder cylinder, t_ray old_ray)
{
	double	a;
	double	b;
	double	c;
	double	disc;

	a = (pow(old_ray.direction.x, 2) + pow(old_ray.direction.y, 2));
	if (comparing_double(a, 0.0))
		return (NULL);
	b = (2 * old_ray.origin.x * old_ray.direction.x) + (2 * old_ray.origin.z * old_ray.direction.z);
	c = (pow(old_ray.origin.x, 2) + pow(old_ray.origin.z, 2) - 1);
	disc = pow(b, 2) - 4 * a * c;
	if (disc < 0)
		return (NULL);
	else
		return(intersection());
}


/*main to test*/


int main()
{
//	|        ORIGIN                          |           VECTOR                            |
	t_vector p1 = create_point(0, 0, -5);	t_vector direction1 = create_vector(0, 0, 1);
	t_vector p2 = create_point(0, 0, -5);	t_vector direction2 = create_vector(0, 0, 1);
	t_vector p3 = create_point(0, 0, -5);	t_vector direction3 = create_vector(0, 0, 1);


}

