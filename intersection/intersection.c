/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersection.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atucci <atucci@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 14:50:26 by atucci            #+#    #+#             */
/*   Updated: 2024/07/31 11:18:41 by atucci           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

t_type	string_to_type(char *type)
{
	if (my_strcmp(type, "sp") == 0)
		return (T_SPHERE);
	if (my_strcmp(type, "pl") == 0)
		return (T_PLANE);
	if (my_strcmp(type, "cy") == 0)
		return (T_CYLINDER);
	else
		return (T_CAMERA); // THIS IS TO COMPILE
}

t_intersection	intersection(double t, char *type, void *obj_address)
{
	t_intersection	new;

	new.t = t;
	new.obj.type = string_to_type(type);
	new.obj.address = obj_address;
	printf("\t\t%sintersection func%s %p\n", YELLOW, RESET, obj_address);
	return (new);
}
