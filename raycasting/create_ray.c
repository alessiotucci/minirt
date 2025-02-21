/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_ray.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftroise <ftroise@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 16:27:05 by atucci            #+#    #+#             */
/*   Updated: 2025/02/19 15:18:00 by atucci           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

t_ray	create_ray(t_vector origin, t_vector direction)
{
	t_ray	new_ray;

	new_ray.origin = origin;
	new_ray.direction = direction;
	return (new_ray);
}

void	print_ray(t_ray ray)
{
	printf("%sRAY%s\n", RED, RESET);
	printf("%sorigin%s ", YELLOW, RESET);
	print_vector(ray.origin);
	printf("%sdirection%s ", YELLOW, RESET);
	print_vector(ray.direction);
}

// ray.origin + ray.direction * t;
t_vector	position_ray(t_ray ray, double t)
{
	t_vector	result;
	t_vector	final_result;

	result = multiplication(ray.direction, t);
	final_result = add(ray.origin, result);
	return (final_result);
}
/* main to test out the function */
/*
int	main()
{
	printf("%s FIRST TEST!%s (1) \n", RED, RESET);
	t_vector	my_origin = create_point(1, 2, 3);
	t_vector	my_direction = create_vector(4, 5, 6);
	t_ray new = create_ray(my_origin, my_direction);
	print_ray(new);

	printf("%s TEST!%s (2) \n", RED, RESET);
	t_vector	org = create_point(2, 3, 4);
	t_vector	dir = create_vector(1, 0, 0);
	t_ray n = create_ray(org, dir);
	t_vector	result2= position_ray(n, 0);
	print_vector(result2);

	printf("%s TEST!%s (3) \n", RED, RESET);
	t_vector	result3 = position_ray(n, 1);
	print_vector(result3);

	printf("%s TEST!%s (4) \n", RED, RESET);
	t_vector	result4 = position_ray(n, -1);
	print_vector(result4);

	printf("%s TEST!%s (5) \n", RED, RESET);
	t_vector	result5 = position_ray(n, 2.5);
	print_vector(result5);

	return (0);
}
*/

//TODO: CHECK THE LEAKS WITH THIS COMMANDS
//valgrind   --leak-check=full --show-leak-kinds=all ./a.out
