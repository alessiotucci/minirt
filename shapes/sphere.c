/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftroise <ftroise@student.42roma.it>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 19:26:21 by atucci            #+#    #+#             */
/*   Updated: 2024/09/16 09:39:20 by ftroise          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

/*
typedef struct s_sphere
{
	char		*identifier;
	t_vector	center;
	double		diameter;
	t_color		color;
}	t_sphere;
*/

t_sphere	create_sphere(char *id, t_vector center, double d, t_color c)
{
	t_sphere	new_sphere;
	double		**def;

	def = malloc_matrix(4, 4);
	create_identity_matrix(def);
	new_sphere.identifier = id;
	new_sphere.center = center;
	new_sphere.diameter = d;
	new_sphere.transform = def;
	new_sphere.color = c;
	new_sphere.material = material();
	return (new_sphere);
}

int	calculate_sphere_color(t_intersection *intersection)
{
	t_sphere	*sphere;

	sphere = (t_sphere *)intersection->obj.address;
	return (create_trgb(sphere->color));
}
