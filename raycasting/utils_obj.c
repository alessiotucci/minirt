/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_obj.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atucci <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 12:29:36 by atucci            #+#    #+#             */
/*   Updated: 2024/07/24 12:44:49 by atucci           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

/* just a function that print the type of the object based of the enums */
void	print_type(t_object obj)
{
	if (obj->type == SPHERE)
		print_single_sphere((t_sphere *)obj->obj);
	if (obj->type == PLANE)
		print_single_plane((t_plane *)obj->obj);
	if (obj->type == CYLINDER)
		print_single_cylinder((t_cylinder *)obj->obj);
	else
		printf("value: %d, do not MATCH\n", obj->type);
}
