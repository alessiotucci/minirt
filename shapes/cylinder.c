/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atucci <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 19:26:30 by atucci            #+#    #+#             */
/*   Updated: 2025/02/19 10:28:19 by atucci           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

void	update_cylinder(t_cylinder *my_cylinder)
{
	my_cylinder->min = -my_cylinder->height / 2;
	my_cylinder->max = my_cylinder->height / 2;
	printf("Updating min and max\nupdate Cylinder\n\n");
}

t_cylinder	create_cylinder(char *id, t_vector center, double d, t_color c)
{
	t_cylinder	new_cylinder;
	double		**def;

	def = malloc_matrix(4, 4);
	create_identity_matrix(def);
	new_cylinder.identifier = id;
	new_cylinder.center = center;
	new_cylinder.diameter = d;
	new_cylinder.color = c;
	new_cylinder.transform = def;
	new_cylinder.material = material(create_color(115, 135, 22));
	new_cylinder.closed = 0;
	return (new_cylinder);
}

void	set_cylinder_cap(t_cylinder *cylinder)
{
	if (cylinder->closed == 0)
		cylinder->closed = 1;
	else
		cylinder->closed = 0;
}

void	set_cylinder_size(t_cylinder *cylinder, double min, double max)
{
	cylinder->min = min;
	cylinder->max = max;
}
