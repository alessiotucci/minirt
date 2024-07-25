/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_obj.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atucci <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 12:29:36 by atucci            #+#    #+#             */
/*   Updated: 2024/07/25 16:17:55 by atucci           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

/* just a function that print the type of the object based of the enums */
int	print_type(t_object obj)
{
	printf("Intersection OBJECT of type: ");
	if (obj.type == T_SPHERE)
		return (printf("%sSPHERE%s\n", RED, RESET));
	if (obj.type == T_PLANE)
		return (printf("%sPLANE%s\n", YELLOW, RESET));
	if (obj.type == T_CYLINDER)
		return (printf("%sCYLINDER%s\n", BLUE, RESET));
	else
		return (printf("NULL %d\n", obj.type));
}

/*
int main()
{
	printf("%s WASTING TIME%s\n", RED, RESET);
	return (0);
}
*/

// gcc utils_obj.c ../extra/print_debug.c
