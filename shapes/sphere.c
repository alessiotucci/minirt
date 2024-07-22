/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftroise <ftroise@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 19:26:21 by atucci            #+#    #+#             */
/*   Updated: 2024/07/22 18:01:11 by ftroise          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

/*
typedef struct s_sphere
{
	char		*identifier;
	t_vector	center;
	double		diameter;
	t_color		color;
}	t_sphere;
*/

t_sphere	create_sphere(char *id, t_vector center, double d, t_color c)
{
	t_sphere	new_sphere;

	new_sphere.identifier = id;
	new_sphere.center = center;
	new_sphere.diameter = d;
	(void)c;
	//new_shere.color = c;
	return (new_sphere);
}

t_color** create_canvas(int width, int height)
{
    t_color** canvas = (t_color**)malloc(height * sizeof(t_color*));
    for (int i = 0; i < height; i++) {
        canvas[i] = (t_color*)malloc(width * sizeof(t_color));
        for (int j = 0; j < width; j++) {
            canvas[i][j] = (t_color){0, 0, 0};
        }
    }
    return canvas;
}

void write_pixel(t_color** canvas, int x, int y, t_color color)
{
    if (x >= 0 && x < DEFAULT_WIDTH && y >= 0 && y < DEFAULT_HEIGHT)
        canvas[y][x] = color;
}


void render_sphere_image(t_sphere sphere)
{
    const double wall_size = 7.0;
    const double wall_z = 10.0;
    const double pixel_size = wall_size / DEFAULT_WIDTH;
    const double half = wall_size / 2;

	t_intersection xs;
    t_color** canvas = create_canvas(DEFAULT_WIDTH, DEFAULT_HEIGHT);
    t_color red = {255, 0, 0};
    t_vector ray_origin = create_point(0, 0, -5);

    int y = 0;
    while (y < DEFAULT_HEIGHT)
	{
        double world_y = half - pixel_size * y;
        int x = 0;
        while (x < DEFAULT_WIDTH)
		{
            double world_x = -half + pixel_size * x;
            t_vector position = create_point(world_x, world_y, wall_z);
            t_ray ray = create_ray(ray_origin, normalization(create_vector(position.x - ray_origin.x, position.y - ray_origin.y, position.z - ray_origin.z)));
            xs = intersect_sphere(sphere, ray);

            if (hit(xs))
                write_pixel(canvas, x, y, red);
            x++;
        }
        y++;
    }

    // Salva la tela in un file PPM
    FILE *file = fopen("output.ppm", "w");
    fprintf(file, "P3\n%d %d\n255\n", DEFAULT_WIDTH, DEFAULT_HEIGHT);
    for (int i = 0; i < DEFAULT_HEIGHT; i++) {
        for (int j = 0; j < DEFAULT_WIDTH; j++) {
            t_color pixel = canvas[i][j];
            fprintf(file, "%d %d %d ", pixel.r, pixel.g, pixel.b);
        }
    }
    fclose(file);

    // Libera la memoria
    for (int i = 0; i < DEFAULT_HEIGHT; i++) {
        free(canvas[i]);
    }
    free(canvas);
}