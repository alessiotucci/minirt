/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atucci <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 19:26:21 by atucci            #+#    #+#             */
/*   Updated: 2024/06/02 16:59:16 by atucci           ###   ########.fr       */
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

	new_shere.identifier = id;
	new_shere.center = center;
	new_shere.diameter = d;
	(void)c;
	//new_shere.color = c;
	return (new_shere);
}
