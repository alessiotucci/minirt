/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atucci <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 19:26:30 by atucci            #+#    #+#             */
/*   Updated: 2024/12/13 19:29:08 by atucci           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

t_cylinder	create_cylinder(char *id, t_vector center, double d, t_color c)
{
	t_cylinder	new_cylinder;
	double		**def;

	def = malloc_matrix(4, 4);
	create_identity_matrix(def);
	new_cylinder.identifier = id;
	new_cylinder.center = center;
//	new_cylinder.axis;
	new_cylinder.diameter = d;
//	new_cylinder.height;
	new_cylinder.color = c;
	new_cylinder.transform = def;
	new_cylinder.material = material();
	return (new_cylinder);
}
