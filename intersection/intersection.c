/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersection.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atucci <atucci@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 14:50:26 by atucci            #+#    #+#             */
/*   Updated: 2024/07/25 15:41:08 by atucci           ###   ########.fr       */
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

t_object	create_object(char *type, void *object)
{
	t_object	new;

	new.type = string_to_type(type);
	new.obj = object;
	return (new);
}

t_intersection	intersection(double t, char *type, void *object)
{
	t_intersection	new;

	new.t = t;
	new.obj = create_object(type, object);
	return (new);
}
