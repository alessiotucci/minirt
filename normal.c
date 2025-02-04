/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   normal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atucci <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 14:24:11 by atucci            #+#    #+#             */
/*   Updated: 2025/02/04 16:31:24 by atucci           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

//reason by gpt
t_vector local_point_in_cylinder(t_cylinder *cylinder, t_vector point)
{
    // Subtract the cylinder’s center (for the XZ coordinates)
    // You may or may not want to affect the Y coordinate depending on your transform;
    // here we assume the cylinder’s transform has already been applied so that the cylinder’s
    // center in XZ is given by cylinder->center.x and cylinder->center.z.
    t_vector local;
    local.x = point.x - cylinder->center.x;
    local.y = point.y;  // leave Y alone
    local.z = point.z - cylinder->center.z;
    local.w = point.w;  // keep the w component unchanged
    return local;
}
//reasoning by gpt fix this
t_vector default_cylinder_normal(t_cylinder *cylinder, t_vector point)
{
    // Transform the point into cylinder-local coordinates (in XZ)
    t_vector local = local_point_in_cylinder(cylinder, point);
    // Use the actual squared radius of the cylinder
    double r_squared = pow(cylinder->diameter / 2, 2);

    // Check if the point is on the top cap
    if ((pow(local.x, 2) + pow(local.z, 2)) < r_squared &&
        local.y >= cylinder->max - EPSILON)
    {
        return create_vector(0, 1, 0);
    }
    // Check if the point is on the bottom cap
    else if ((pow(local.x, 2) + pow(local.z, 2)) < r_squared &&
             local.y <= cylinder->min + EPSILON)
    {
        return create_vector(0, -1, 0);
    }
    // Otherwise, for the lateral surface, compute the normal using the local XZ values
    else
    {
        return normalization(create_vector(local.x, 0, local.z));
    }
}

/*please rename this function */
t_vector v2normal_at(t_object obj, t_vector point)
{
	t_sphere	*sphere;
	t_plane		*plane;
	t_cylinder	*cylinder; (void)cylinder;

	if (obj.type == T_SPHERE)
	{
		sphere = (t_sphere *)obj.address; // casting
		return normalization(subtract(point, sphere->center));
	}
	if (obj.type == T_PLANE)
	{
		plane = (t_plane *)obj.address;
		return (plane->normal);
	}
	if (obj.type == T_CYLINDER)
	{
		//printf("V2Normal_at, cylinder\n");
		cylinder = (t_cylinder *)obj.address;
		return (default_cylinder_normal(cylinder, point));
	}
	printf("v2normal failure: obj TYPE not found\n");
	exit(-42);
}

// Function to calculate the reflection of a vector
/*
t_vector reflect(t_vector in, t_vector normal)
{
	double		dot_product = dot(in, normal);
	t_vector	scaled_normal = multiplication(normal, 2 * dot_product);
	t_vector	reflection = subtract(in, scaled_normal);
	return (reflection);
}
*/
// reflection = in - normal * 2 * dot(in, normal)
t_vector	reflect(t_vector in, t_vector normal)
{
	return (subtract(in, multiplication(normal, 2 * dot(in, normal))));
}

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

/*
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

	printf("\n%sNext test\t*\t*\t*%s\n", GREEN, RESET);

	printf("\n\n%sScenario: 1%s Reflecting a vector appraching at 45degrees\n", RED, RESET);
	t_vector v1 = create_vector(1, -1, 0);
	t_vector n1 = create_vector(0, 1, 0);
	t_vector res1 = reflect(v1, n1);
	print_vector(res1);

	printf("\n\n%sScenario: 2%s Reflecting a vector off a slanted surfaces\n", RED, RESET);
	t_vector v2 = create_vector(0, -1, 0);
	t_vector n2 = create_vector(sqrt(2) / 2, sqrt(2) / 2, 0);
	t_vector res2 = reflect(v2, n2);
	print_vector(res2);

}
*/


// Main function to test the normal computation on a cylinder
/*
int main()
{
	// Create a cylinder object
	t_cylinder cyl;
	cyl.center = create_vector(0, 0, 0);
	cyl.axis = create_vector(0, 1, 0);
	cyl.diameter = 14.2;
	cyl.height = 21.42;
	cyl.color.r = 10;
	cyl.color.g = 0;
	cyl.color.b = 255;

	// Create an object for the cylinder
	t_object obj;
	obj.type = T_CYLINDER;
	obj.address = &cyl;

	// Define points on the cylinder
	t_vector points[] =
	{
		create_point(1, 0, 0),	// Point on the curved surface
		create_point(0, 5, -1),  // Point on the top cap
		create_point(0, -2, 1),   // Point on the bottom cap
		create_point(-1, 1, 0)	// Point on the curved surface
	};
	// Test the normal computation
	for (int i = 0; i < 4; i++)
	{
		t_vector normal = v2normal_at(obj, points[i]);
		printf("Point: (%f, %f, %f)\t | ", points[i].x, points[i].y, points[i].z);
		printf("Normal: (%f, %f, %f)\n", normal.x, normal.y, normal.z);
	}
	return 0;
}
*/

/*
int main()
{
	// Create a cylinder object
	t_cylinder cyl;
	cyl.center = create_vector(0, 0, 0);
	cyl.axis = create_vector(0, 1, 0);
	cyl.diameter = 14.2;
	cyl.height = 21.42;
	cyl.color.r = 10;
	cyl.color.g = 0;
	cyl.color.b = 255;
	set_cylinder_size(&cyl, 1, 2);
	set_cylinder_cap(&cyl);

	// Create an object for the cylinder
	t_object obj;
	obj.type = T_CYLINDER;
	obj.address = &cyl;

	// Define points on the cylinder
	t_vector points[] =
	{
		create_point(0, 1, 0),
		create_point(0.5, 1, 0),
		create_point(0, 1, 0.5),
		create_point(0, 2, 0),
		create_point(0.5, 2, 0),
		create_point(0, 2, 0.5)
	};
	// Test the normal computation
	for (int i = 0; i < 6; i++)
	{
		t_vector normal = v2normal_at(obj, points[i]);
		printf("Point: (%f, %f, %f)\t | ", points[i].x, points[i].y, points[i].z);
		printf("Normal: (%f, %f, %f)\n", normal.x, normal.y, normal.z);
	}
	return 0;
}
*/
