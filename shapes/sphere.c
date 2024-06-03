/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atucci <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 19:26:21 by atucci            #+#    #+#             */
/*   Updated: 2024/06/03 11:13:02 by atucci           ###   ########.fr       */
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

	new_sphere.identifier = id;
	new_sphere.center = center;
	new_sphere.diameter = d;
	(void)c;
	//new_shere.color = c;
	return (new_sphere);
}
