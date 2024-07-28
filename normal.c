/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   normal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atucci <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 14:24:11 by atucci            #+#    #+#             */
/*   Updated: 2024/07/28 14:46:03 by atucci           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

// You may assume that the point will always be on the surface of the sphere
t_vector	normal_at(t_sphere sphere, t_vector point)
{
	(void)sphere;
	t_vector	t;

	t = create_point(0, 0, 0);
	return (normalization(subtract(point, t)));
}

int	main()
{
	t_color bogus; bogus.r = 0; bogus.g = 0; bogus.b = 0;
	t_vector point = create_point(0, 0, 0);
	t_sphere s = create_sphere("sp", point, 1.0, bogus); // create unit sphere

	printf("\n\n%sScenario: 1%s The normal on a sphere at a point on the x axis\n", RED, RESET);
	t_vector point1 = create_point(1, 0, 0);
	t_vector result1 = normal_at(s, point1);
	print_vector(result1);
	printf("---");

	printf("\n\n%sScenario: 2%s The normal on a sphere at a point on the y axis\n", RED, RESET);
	t_vector point2 = create_point(0, 1, 0);
	t_vector result2 = normal_at(s, point2);
	print_vector(result2);
	printf("---");

	printf("\n\n%sScenario: 3%s The normal on a sphere at a point on the z axis\n", RED, RESET);
	t_vector point3 = create_point(0, 0, 1);
	t_vector result3 = normal_at(s, point3);
	print_vector(result3);
	printf("---");

	printf("\n\n%sScenario: 4%s The normal on a sphere at a point on non-axis\n", RED, RESET);
	t_vector point4 = create_point(sqrt(3) / 3, sqrt(3) / 3, sqrt(3) / 3);
	t_vector result4 = normal_at(s, point4);
	print_vector(result4);
	printf("---");

	printf("\n\n%sScenario: 5%s The normal is a normalized vector\n", RED, RESET);
}
