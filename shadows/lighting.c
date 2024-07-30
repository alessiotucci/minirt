/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lighting.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atucci <atucci@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 14:56:06 by atucci            #+#    #+#             */
/*   Updated: 2024/07/30 12:33:36 by atucci           ###   ########.fr       */
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
	printf("multiplying colors ... ");
	t_color effective_color = multiply_colors(mat.color, light.color);
	printf("Effective Color:");
	print_color(effective_color);

	// Light vector: from light position to the point
	t_vector light_v = normalization(subtract(light.position, point));
	printf("Light Vector:");
	print_vector(light_v);

	// Ambient contribution
	t_color ambient = multiply_color_by_scalar(effective_color, mat.ambient);
	printf("Ambient:");
	print_color(ambient);

	// Light dot normal
	double light_dot_normal = dot(light_v, normal);
	printf("Light Dot Normal: %lf\n", light_dot_normal);

	t_color diffuse, specular;
	if (light_dot_normal < 0)
	{
		diffuse = create_color(0, 0, 0); // black
		specular = create_color(0, 0, 0); // black
		printf("Light behind the surface. Diffuse and Specular set to black.\n");
	}
	else
	{
		// Diffuse contribution
		diffuse = multiply_color_by_scalar(multiply_color_by_scalar(effective_color, mat.diffuse), light_dot_normal);
		printf("Diffuse:");
		print_color(diffuse);

		// Reflection vector
		t_vector reflect_v = reflect(negate(light_v), normal);
		printf("Reflect Vector:");
		print_vector(reflect_v);

		// Reflect dot eye
		double reflect_dot_eye = dot(reflect_v, eye);
		printf("Reflect Dot Eye: %lf\n", reflect_dot_eye);

		if (reflect_dot_eye <= 0)
		{
			specular = create_color(0, 0, 0); // black
			printf("Reflect Dot Eye <= 0. Specular set to black.\n");
		}
		else
		{
			// Specular contribution
			double factor = pow(reflect_dot_eye, mat.shininess);
			specular = multiply_color_by_scalar(multiply_color_by_scalar(light.color, mat.specular), factor);
			printf("Specular:");
			print_color(specular);
		}
	}

	// Final color
	t_color final_color = add_colors(add_colors(ambient, diffuse), specular);
	return (final_color);
}



/*THIS is my first try: ignore that is not norminetted yet
t_color	lighting(t_material mat, t_light light, t_vector point, t_vector eye, t_vector normal)
{
	//(void)mat;(void)light;(void)point;(void)eye;(void)normal;
	//t_color	c = create_color(1, 1, 1);
	
	t_color	diffuse;
	t_color	specular;
	t_color	ambient;

	//1) var_effective_color: create a new color, by multiplying mat.color * light.color;
	t_color	effective_color = multiply_colors(mat.color, light.color);
	//2) var_light_v: create a vector by subtracting the light.position - point;
	//3) remember to normalize this vector;
	t_vector	light_v = normalization(subtract(light.position, point));
	//4) ambient: create an other color, by multiplying a color by a scalar ->var_effective_color * material.ambient;
	ambient = multiply_color_by_scalar(effective_color, mat.ambient);
	//5) var_light_dot_normal: create a dot product with var_light_v and normal;
	double	light_dot_normal = dot(light_v, normal);
	if (light_dot_normal < 0)
	{
		diffuse = create_color(0, 0, 0);//black
		specular = create_color(0, 0, 0);//black
	}
	else
	{
			// 1) diffuse = moltiplication between var_effective_color * material.diffure [it is a scalar] * var_light_dot_normal [it is a scalar]
			diffuse = multiply_color_by_scalar(multiply_color_by_scalar(effective_color, mat.diffuse), light_dot_normal);
			// 2) var_reflect_v = reflect(-var_light_v, normal);
			t_vector reflect_v = reflect(negate(light_v), normal);
			// 3) reflect_dot_eye = dot(reflect_v, eye);
				double reflect_dot_eye = dot(reflect_v, eye);
				if (reflect_dot_eye <= 0)
				// 1) specular = black;
					specular = create_color(0, 0, 0);//black
				else
				{
					//1) var_factor = pow(var_reflect_dot_eye, material.shininess)
					double factor = pow(reflect_dot_eye, mat.shininess);
					//2) specular = light.color * material.specular [it is a scalar] * factor [it is a scalar]
					specular = multiply_color_by_scalar(multiply_color_by_scalar(light.color, mat.specular), factor);
				}
	}
	//6) return (ambient + diffuse + specular);
	return (add_colors(add_colors(ambient, diffuse), specular));
	//return (c);
}
*/

/* given the assumption */
/*
int	main()
{
	printf("Given the assumption of material and point\n");
	t_material	m = material();
	t_vector	position = create_point(0, 0, 0);

	printf("\n\n%sScenario: 1%s Lighting with the eye between the light and the surface\n", RED, RESET);
	t_vector	eye_v1 = create_vector(0, 0, -1);
	t_vector	normal_v1 = create_vector(0, 0, -1);
	t_light		light1 = point_light(create_point(0, 0, -10), create_color(1, 1, 1));
	t_color result1 = lighting(m, light1, position, eye_v1, normal_v1);
	print_color(result1);
	printf("❌ %sTEST FAILED%s❌\n", BG_RED, BG_RESET);
	//printf("✅ %sTEST PASSED%s✅\n", BG_GREEN, BG_RESET);

	exit(-42);
	printf("\n\n%sScenario: 2%s Lighting with the eye between the light and the surface, eye offset 45°\n", RED, RESET);
	t_vector	eye_v2 = create_vector(0, sqrt(2) / 2, sqrt(2) / -2);
	t_vector	normal_v2 = create_vector(0, 0, -1);
	t_light		light2 = point_light(create_point(0, 0, -10), create_color(1, 1, 1));
	t_color result2 = lighting(m, light2, position, eye_v2, normal_v2);
	print_color(result2);

	printf("\n\n%sScenario: 3%s Lighting with the eye opposite the light and the surface, eye offset 45°\n", RED, RESET);
	t_vector	eye_v3 = create_vector(0, 0, -1);
	t_vector	normal_v3 = create_vector(0, 0, -1);
	t_light		light3 = point_light(create_point(0, 10, -10), create_color(1, 1, 1));
	t_color result3 = lighting(m, light3, position, eye_v3, normal_v3);
	print_color(result3);

	printf("\n\n%sScenario: 4%s Lighting with the eye in the path of the reflection vector\n", RED, RESET);
	t_vector	eye_v4 = create_vector(sqrt(2) / -2, sqrt(2) / -2, -1);
	t_vector	normal_v4 = create_vector(0, 0, -1);
	t_light		light4 = point_light(create_point(0, 0, -10), create_color(1, 1, 1));
	t_color result4 = lighting(m, light4, position, eye_v4, normal_v4);
	print_color(result4);

	printf("\n\n%sScenario: 5%s Lighting with the light behind the surface\n", RED, RESET);
	t_vector	eye_v5 = create_vector(0, 0, -1);
	t_vector	normal_v5 = create_vector(0, 0, -1);
	t_light		light5 = point_light(create_point(0, 0, 10), create_color(1, 1, 1));
	t_color result5 = lighting(m, light5, position, eye_v5, normal_v5);
	print_color(result5);
	//
}
*/
