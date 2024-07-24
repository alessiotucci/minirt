/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_obj.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atucci <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 12:29:36 by atucci            #+#    #+#             */
/*   Updated: 2024/07/24 15:40:37 by atucci           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

/* just a function that print the type of the object based of the enums */
void	print_type(t_object obj)
{
	printf("INTERSECTION OBJECT RECOGNITION: ");
	if (obj.type == T_SPHERE)
	{
		printf("%sSPHERE%s\n", RED, RESET);
		//print_single_sphere((t_sphere *)obj.obj);
	}
	if (obj.type == T_PLANE)
	{
		printf("%sPLANE%s\n", YELLOW, RESET);
		//print_single_plane((t_plane *)obj.obj);
	}
	if (obj.type == T_CYLINDER)
	{
		printf("%sCYLINDER%s\n", BLUE, RESET);
		//print_single_cylinder((t_cylinder *)obj.obj);
	}
	else
		printf("value: %d, do not MATCH\n", obj.type);
}

/*
int main()
{
	printf("%s WASTING TIME%s\n", RED, RESET);
	return (0);
}
*/

// gcc utils_obj.c ../extra/print_debug.c
