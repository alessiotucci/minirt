/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   material.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atucci <atucci@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 14:55:51 by atucci            #+#    #+#             */
/*   Updated: 2025/02/07 13:37:25 by atucci           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"


t_material	material(t_color color)
{
	t_material	standard;

	//standard.color = create_color(255, 125, 44);
	standard.color = color;
	standard.ambient = 0.1;
	standard.diffuse = 0.9;
	standard.specular = 0.9;
	standard.shininess = 200.0;
	return (standard);

}

void	print_material(t_material mat)
{
	printf("PRINT MATERIAL\ncolor: ");
	print_color(mat.color);
	printf("ambient: %lf\n", mat.ambient);
	printf("diffuse: %lf\n", mat.diffuse);
	printf("specular: %lf\n", mat.specular);
	printf("sphininess: %lf\n", mat.shininess);
}


void	assign_material_sphere(t_sphere *s, t_material new)
{
	s->material = new;
}

/*
int	main()
{
	t_color bogus = create_color(0, 0, 0);
	t_vector point = create_point(0, 0, 0);
	t_sphere s = create_sphere("sp", point, 1.0, bogus); // create unit sphere
	printf("\n\n%sScenario: 1%s The default material\n", RED, RESET);
	t_material	new = material();
	print_material(new);
	printf("---");

	printf("\n\n%sScenario: 2%s A sphere has a default material\n", RED, RESET);
	printf("Printing a single sphere...");
	print_single_sphere(&s);
	printf("---");

	printf("\n\n%sScenario: 3%s A sphere may be assigned a material\n", RED, RESET);
	new.ambient = 1.0;
	assign_material_sphere(&s, new);
	printf("After assigning a new material...");
	print_single_sphere(&s);
	printf("---");
}

*/
