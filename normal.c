/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   normal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atucci <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 14:24:11 by atucci            #+#    #+#             */
/*   Updated: 2025/02/08 16:28:17 by atucci           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

//REASON  gpt
static t_vector get_plane_normal(t_plane *pl, t_ray ray)
{
    t_vector normal;

    // Get the stored normal.
    normal = pl->normal;
	printf("get_plane_normal: FUNCTION CALL!\n");
    // If the dot product between the ray's direction and the normal is positive,
    // then the ray is coming from behind the plane.
    // Flip the normal so that it faces the ray.
    if (dot(ray.direction, normal) > 0)
	{
        normal = multiplication(normal, -1);
		printf("dot(ray.direction, normal) > 0: [%d]\n", dot(ray.direction, normal) > 0 );
	}

    // Return the (assumed to be already normalized) normal.
    return normal;
}


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
//TODO:
t_vector default_cylinder_normal(t_cylinder *cylinder, t_vector point)
{
    t_vector local;
    double r_squared;
    double dist_xz;
    double blend;(void)blend;
    t_vector lateral;(void)lateral;
    t_vector cap;(void)cap;
    t_vector blended;(void)blended;

    // Convert the point to the cylinder's local coordinate system (for XZ)
    local = local_point_in_cylinder(cylinder, point);
    r_squared = pow(cylinder->diameter / 2, 2);
    dist_xz = pow(local.x, 2) + pow(local.z, 2);

    // If the point is within the cap's circular boundary
    if (dist_xz < r_squared)
    {
        // If the Y coordinate is almost equal to the top cap...
        if (comparing_double(local.y, cylinder->max))
            return create_vector(0, 1, 0);
        // ...or almost equal to the bottom cap.
        else if (comparing_double(local.y, cylinder->min))
            return create_vector(0, -1, 0);
    }
    // For points clearly on the lateral surface, return the normalized lateral normal.
    return normalization(create_vector(local.x, 0, local.z));
}

/*please rename this function */					//TODO
t_vector v2normal_at(t_object obj, t_vector point, t_ray r)
{
	t_sphere	*sphere;
	t_plane		*plane;
	t_cylinder	*cylinder;

	if (obj.type == T_SPHERE)
	{
		sphere = (t_sphere *)obj.address; // casting
		return normalization(subtract(point, sphere->center));
	}
	if (obj.type == T_PLANE)
	{
		plane = (t_plane *)obj.address;
		return get_plane_normal(plane, r);
		//return (plane->normal);
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


/* --- Test Program --- GPT HAS REASONING NOW
int main(void)
{
    t_cylinder cyl;
    t_object obj;
    t_vector test_points[6];
    t_vector normal;
    int i;

    //  Set up a cylinder.
    //  For this test, we assume the cylinder is defined in its object space as follows:
    //  - Center: (0, 0, 0)  (i.e., the XZ part of the center is at the origin)
    //  - Axis: (0, 1, 0)    (vertical)
    //  - Diameter: 14.2 (so radius = 7.1)
    //  - Height: 21.42, and we choose Option 2 (centered), so the caps are at:
    //       min = -height/2, max = height/2.
     
    cyl.center = create_vector(0, 0, 0);
    cyl.axis = create_vector(0, 1, 0);
    cyl.diameter = 14.2;
    cyl.height = 21.42;
    cyl.min = -cyl.height / 2.0;  // e.g., -10.71
    cyl.max = cyl.height / 2.0;   // e.g., 10.71
    // (Other fields like color, transform, material are not used for normal calculation.)
    cyl.color = parse_color("10,0,255");
    // For this test, assume an identity transformation.
    // (You can set cyl.transform to an identity matrix or NULL if your code interprets it as identity.)
    cyl.transform = NULL;

    // Create an object wrapper for the cylinder //
    obj.type = T_CYLINDER;
    obj.address = &cyl;

    // Define test points on the cylinder:
    // 0) Top cap center: should yield (0, 1, 0)
    // 1) Bottom cap center: should yield (0, -1, 0)
    // 2) Lateral surface: a point on the side; for example, (7.1, 0, 0)
    // 3) Lateral surface: another point, say (-7.1, 0, 0)
    // 4) A point near the top edge (transition between lateral and cap)
    // 5) A point near the bottom edge
    //
    test_points[0] = create_point(0, cyl.max, 0);       // Top cap center
    test_points[1] = create_point(0, cyl.min, 0);       // Bottom cap center
    test_points[2] = create_point(cyl.diameter / 2, 0, 0);  // Lateral surface on +X
    test_points[3] = create_point(-cyl.diameter / 2, 0, 0); // Lateral surface on -X
    test_points[4] = create_point(cyl.diameter / 2, cyl.max - 0.001, 0); // Near top cap edge
    test_points[5] = create_point(cyl.diameter / 2, cyl.min + 0.001, 0); // Near bottom cap edge

    // Test the normal computation for each point //
    for (i = 0; i < 6; i++)
    {
        normal = v2normal_at(obj, test_points[i]);
        printf("Point: (%.3f, %.3f, %.3f) -> Normal: (%.3f, %.3f, %.3f)\n",
            test_points[i].x, test_points[i].y, test_points[i].z,
            normal.x, normal.y, normal.z);
    }
    return 0;
}
*/
