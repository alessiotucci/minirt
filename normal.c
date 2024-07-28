/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   normal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atucci <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 14:24:11 by atucci            #+#    #+#             */
/*   Updated: 2024/07/28 16:01:06 by atucci           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

// You may assume that the point will always be on the surface of the sphere
t_vector	normal_at(t_sphere sphere, t_vector world_point)
{
	t_vector	object_point;
	t_vector	object_normal;
	t_vector	world_normal;
	t_vector	point;

	object_point = matrix_x_vector(inversing_matrix(4, sphere.transform) , world_point);
	point = create_point(0, 0, 0);
	object_normal = subtract(object_point, point);
	world_normal = matrix_x_vector(transposing(4, 4, inversing_matrix(4, sphere.transform)), object_normal);
	world_normal.w = 0;
	return (normalization(world_normal));

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
	if (comparing_vector(result4, normalization(result4)))
		printf("vector from normal is indeed normal\n");

	printf("\n\n%sScenario: 6%s Computing the normal on a translated sphere \n", RED, RESET);
	// sphere s;
	set_sphere_transformations(&s, create_translation_matrix(create_point(0, 1, 0)));
	t_vector point5 = create_point(0, 1.70711, -0.70711);
	t_vector result5 = normal_at(s, point5);
	print_vector(result5);


	printf("\n\n%sScenario: 7%s Computing the normal on a transformed sphere \n", RED, RESET);
	double **m = multiply_matrix(4, 4, create_scaling_matrix(create_point(1, 0.5, 1)), matrix_rotation_z(M_PI / 5)) ;
	set_sphere_transformations(&s, m);
	t_vector point6 = create_point(0, sqrt(2) / 2, sqrt(2) / -2);
	t_vector result6 = normal_at(s, point6);
	print_vector(result6);

}
