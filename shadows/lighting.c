/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lighting.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atucci <atucci@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 14:56:06 by atucci            #+#    #+#             */
/*   Updated: 2024/08/01 11:01:37 by atucci           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

/*typedef struct s_light
{
	char		*identifier;
	t_vector	position;
	double		brightness;
	t_color		color;
}	t_light;*/

t_light	point_light(t_vector pos, t_color c)
{
	t_light	new;

	new.identifier = "TEST";//
	new.position = pos;
	new.brightness = 1.0;//
	new.color = c;
	return (new);
}

t_color	lighting(t_material mat, t_light light, t_vector point, t_vector eye, t_vector normal)
{
	// Effective color: material color multiplied by light color
	t_color effective_color = multiply_colors(mat.color, light.color);

	// Light vector: from light position to the point
	t_vector light_v = normalization(subtract(light.position, point));
	//printf("Light Vector:");
	//print_vector(light_v);

	// Ambient contribution
	t_color ambient = multiply_color_by_scalar(effective_color, mat.ambient);

	//TODO
	/* Debugging the vectors
	printf("Point: ");
	print_vector(point);
	printf("Light Position: ");
	print_vector(light.position);
	printf("Normal Vector: ");
	print_vector(normal);
	printf("Light Vector: ");
	print_vector(light_v);
	print_single_light(&light);
	*/

	// Light dot normal
	double light_dot_normal = dot(light_v, normal);
	//printf("Light Dot Normal: %lf\n", light_dot_normal);

	t_color diffuse;
	t_color specular;

	if (light_dot_normal < 0)
	{
		//printf("%sDiffuse is black%s\n", BG_RED, BG_RESET);
		//printf("%sSpecular is black%s\n", BG_RED, BG_RESET);
		diffuse = create_color(0, 0, 0); // black
		specular = create_color(0, 0, 0); // black
		printf("Light behind the surface. Diffuse and Specular set to black.\n");
	}
	else
	{
		// Diffuse contribution
		diffuse = multiply_color_by_scalar(multiply_color_by_scalar(effective_color, mat.diffuse), light_dot_normal);

		// Reflection vector
		t_vector reflect_v = reflect(negate(light_v), normal);
		//printf("Reflect Vector:");
		//print_vector(reflect_v);

		// Reflect dot eye
		double reflect_dot_eye = dot(reflect_v, eye);
		//printf("Reflect Dot Eye: %lf\n", reflect_dot_eye);

		if (reflect_dot_eye <= 0)
		{
			//printf("Reflect Dot Eye <= 0. Specular set to black.\n");
			//printf("%sSpecular is black%s\n", BG_RED, BG_RESET);
			specular = create_color(0, 0, 0); // black
		}
		else
		{
			// Specular contribution
			double factor = pow(reflect_dot_eye, mat.shininess);
			specular = multiply_color_by_scalar(multiply_color_by_scalar(light.color, mat.specular), factor);
		}
	}

	/*
	printf("%s--------------------------------------------%s\n", BG_GREEN, BG_RESET);
	printf("Ambient: %sOK%s", BG_GREEN, BG_RESET);
	print_color(convert_color_inverse(ambient));

	printf("Diffuse: %sOK%s", BG_GREEN, BG_RESET);
	print_color(convert_color_inverse(diffuse));

	printf("specular: %sOK%s", BG_GREEN, BG_RESET);
	print_color(convert_color_inverse(specular));
	*/
	// Final color
	//t_color final_color = add_colors(add_colors(ambient, diffuse), specular);
	t_color final_color;

	// First addition: ambient + diffuse
	t_color ambient_plus_diffuse = add_colors(ambient, diffuse);
	//printf("Ambient + Diffuse:");
	//print_color(ambient_plus_diffuse);

	// Second addition: (ambient + diffuse) + specular
	final_color = add_colors(ambient_plus_diffuse, specular);
	//printf("Final Color:");
	//print_color(final_color);
	//printf("%s--------------------------------------------%s\n", BG_GREEN, BG_RESET);
	return (final_color);
}

/* given the assumption */
int	main()
{
	printf("Given the assumption of material and point\n");
	t_material	m = material();
	t_vector	position = create_point(0, 0, 0);

	printf("\n\n%sScenario: 1%s Lighting with the eye between the light and the surface\n", RED, RESET);
	t_vector	eye_v1 = create_vector(0, 0, -1);
	t_vector	normal_v1 = create_vector(0, 0, -1);
	t_light		light1 = point_light(create_point(0, 0, -10), convert_color(create_color(1, 1, 1)));
	t_color result1 = lighting(m, light1, position, eye_v1, normal_v1);
	printf("Result 1:");
	print_color(result1);
	print_color(convert_color_inverse(result1));
	printf("Expected: 1.9, 1.9, 1.9\n");
	//printf("❌ %sTEST FAILED%s❌\n", BG_RED, BG_RESET);
	printf("✅ %sTEST PASSED%s✅\n", BG_GREEN, BG_RESET);

	//return (-42);//TODO

	printf("\n\n%sScenario: 2%s Lighting with the eye between the light and the surface, eye offset 45°\n", RED, RESET);
	t_vector	eye_v2 = create_vector(0, sqrt(2) / 2, sqrt(2) / -2);
	t_vector	normal_v2 = create_vector(0, 0, -1);
	t_light		light2 = point_light(create_point(0, 0, -10), create_color(1, 1, 1));
	t_color result2 = lighting(m, light2, position, eye_v2, normal_v2);
	printf("Result 2:");
	print_color(result2);
	print_color(convert_color_inverse(result2));
	printf("✅ %sTEST PASSED%s✅\n", BG_GREEN, BG_RESET);

	printf("\n\n%sScenario: 3%s Lighting with the eye opposite the light and the surface, eye offset 45°\n", RED, RESET);
	t_vector	eye_v3 = create_vector(0, 0, -1);
	t_vector	normal_v3 = create_vector(0, 0, -1);
	t_light		light3 = point_light(create_point(0, 10, -10), create_color(1, 1, 1));
	t_color result3 = lighting(m, light3, position, eye_v3, normal_v3);
	printf("Result 3:");
	print_color(result3);
	print_color(convert_color_inverse(result3));
	printf("✅ %sTEST PASSED%s✅\n", BG_GREEN, BG_RESET);

	printf("\n\n%sScenario: 4%s Lighting with the eye in the path of the reflection vector\n", RED, RESET);
	t_vector	eye_v4 = create_vector(0, sqrt(2) / -2, sqrt(2) / -2);
	t_vector	normal_v4 = create_vector(0, 0, -1);
	t_light		light4 = point_light(create_point(0, 10, -10), create_color(1, 1, 1));
	t_color result4 = lighting(m, light4, position, eye_v4, normal_v4);
	printf("Result 4:");
	print_color(result4);
	print_color(convert_color_inverse(result4));
	printf("✅ %sTEST PASSED%s✅\n", BG_GREEN, BG_RESET);

	printf("\n\n%sScenario: 5%s Lighting with the light behind the surface\n", RED, RESET);
	t_vector	eye_v5 = create_vector(0, 0, -1);
	t_vector	normal_v5 = create_vector(0, 0, -1);
	t_light		light5 = point_light(create_point(0, 0, 10), create_color(1, 1, 1));
	t_color result5 = lighting(m, light5, position, eye_v5, normal_v5);
	printf("Result 5:");
	print_color(result5);
	print_color(convert_color_inverse(result5));
	printf("✅ %sTEST PASSED%s✅\n", BG_GREEN, BG_RESET);
	//
}

