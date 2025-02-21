/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type_string.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atucci <atucci@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 15:56:25 by atucci            #+#    #+#             */
/*   Updated: 2025/02/19 16:08:55 by atucci           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

//4
char	*type_to_string(t_type type)
{
	printf("type_to_string: %d\n", type);
	if (type == T_SPHERE)
		return (printf("sphere\n"), "sphere\n");
	if (type == T_PLANE)
		return (printf("plane\n"), "plane\n");
	if (type == T_CYLINDER)
		return (printf("cylinder\n"), "cylinder\n");
	if (type == T_LIGHT)
		return (printf("light\n"), "light\n");
	else
		return (printf("not found:[%d]\n", type), "NOT FOUND\n");
}

//3
t_type	string_to_type(char *type)
{
	if (my_strcmp(type, "sp") == 0)
		return (T_SPHERE);
	if (my_strcmp(type, "pl") == 0)
		return (T_PLANE);
	if (my_strcmp(type, "cy") == 0)
		return (T_CYLINDER);
	else
	{
		printf("Verbose Log: string to type failed!\n");
		exit(-42);
	}
}
