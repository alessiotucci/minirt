/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftroise <ftroise@student.42roma.it>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 14:18:53 by atucci            #+#    #+#             */
/*   Updated: 2024/09/17 10:59:17 by ftroise          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include <stdio.h>


void	init_scene(t_mlx *info, char *mapname)
{
	info->k = 0;
	info->width = DEFAULT_WIDTH;
	info->height = DEFAULT_HEIGHT;
	info->map_name = mapname;
}

static void debug_print_setting(t_setting *setting)
{
    if (setting == NULL)
    {
        printf("t_setting is NULL\n");
        return;
    }

    printf("\n--- Debug: t_setting ---\n");

    // Ambient Light
    if (setting->amb_light != NULL)
    {
        printf("Ambient Light:\n");
        printf("  Ratio: %f\n", setting->amb_light->ratio);
        printf("  Color: R: %f, G: %f, B: %f\n",
            setting->amb_light->color.r,
            setting->amb_light->color.g,
            setting->amb_light->color.b);
    }
    else
    {
        printf("Ambient Light: NULL\n");
    }

    // Camera
    if (setting->camera != NULL)
    {
        printf("Camera:\n");
        printf("  View Point: x: %f, y: %f, z: %f\n",
            setting->camera->viewpoint.x,
            setting->camera->viewpoint.y,
            setting->camera->viewpoint.z);
        printf("  Orientation: x: %f, y: %f, z: %f\n",
            setting->camera->orientation.x,
            setting->camera->orientation.y,
            setting->camera->orientation.z);
        printf("  FOV: %d\n", setting->camera->fov);
    }
    else
    {
        printf("Camera: NULL\n");
    }

    // Lights
    printf("Number of Lights: %d\n", setting->num_lights);
    if (setting->lights != NULL)
    {
        for (int i = 0; i < setting->num_lights; i++)
        {
            printf("  Light[%d]:\n", i);
            printf("    Position: x: %f, y: %f, z: %f\n",
                setting->lights[i]->position.x,
                setting->lights[i]->position.y,
                setting->lights[i]->position.z);
            printf("    Color: R: %f, G: %f, B: %f\n",
                setting->lights[i]->color.r,
                setting->lights[i]->color.g,
                setting->lights[i]->color.b);
            printf("    Brightness: %f\n", setting->lights[i]->brightness);
        }
    }
    else
    {
        printf("Lights: NULL\n");
    }

    // Spheres
    printf("Number of Spheres: %d\n", setting->num_spheres);
    if (setting->spheres != NULL)
    {
        for (int i = 0; i < setting->num_spheres; i++)
        {
            printf("  Sphere[%d]:\n", i);
            printf("    Center: x: %f, y: %f, z: %f\n",
                setting->spheres[i]->center.x,
                setting->spheres[i]->center.y,
                setting->spheres[i]->center.z);
            printf("    Diameter: %f\n", setting->spheres[i]->diameter);
            printf("    Color: R: %f, G: %f, B: %f\n",
                setting->spheres[i]->color.r,
                setting->spheres[i]->color.g,
                setting->spheres[i]->color.b);
        }
    }
    else
    {
        printf("Spheres: NULL\n");
    }

    // Planes
    printf("Number of Planes: %d\n", setting->num_planes);
    if (setting->planes != NULL)
    {
        for (int i = 0; i < setting->num_planes; i++)
        {
            printf("  Plane[%d]:\n", i);
            printf("    Point: x: %f, y: %f, z: %f\n",
                setting->planes[i]->point.x,
                setting->planes[i]->point.y,
                setting->planes[i]->point.z);
            printf("    Normal: x: %f, y: %f, z: %f\n",
                setting->planes[i]->normal.x,
                setting->planes[i]->normal.y,
                setting->planes[i]->normal.z);
            printf("    Color: R: %f, G: %f, B: %f\n",
                setting->planes[i]->color.r,
                setting->planes[i]->color.g,
                setting->planes[i]->color.b);
        }
    }
    else
    {
        printf("Planes: NULL\n");
    }

    // Cylinders
    printf("Number of Cylinders: %d\n", setting->num_cylinders);
    if (setting->cylinders != NULL)
    {
        for (int i = 0; i < setting->num_cylinders; i++)
        {
            printf("  Cylinder[%d]:\n", i);
            printf("    Center: x: %f, y: %f, z: %f\n",
                setting->cylinders[i]->center.x,
                setting->cylinders[i]->center.y,
                setting->cylinders[i]->center.z);
            printf("    Diameter: %f, Height: %f\n",
                setting->cylinders[i]->diameter,
                setting->cylinders[i]->height);
            printf("    Color: R: %f, G: %f, B: %f\n",
                setting->cylinders[i]->color.r,
                setting->cylinders[i]->color.g,
                setting->cylinders[i]->color.b);
        }
    }
    else
    {
        printf("Cylinders: NULL\n");
    }

    // Cones (assuming cones exist in the future)
    printf("Number of Cones: %d\n", setting->num_cones);
    printf("-------------------------\n");
}

//TODO: close the fd, the return of parsing_map();
int	main(int ac, char **av)
{
	t_mlx		info_mlx;
	t_setting	new_setting;

	memset(&info_mlx, 0, sizeof(t_mlx));
	setback_zero(&new_setting);
	if (ac == 2)
	{
		if (parsing_map(av[1], &new_setting))
			return (-1 * ft_printf("%sWrong map: %s%s\n", RED, RESET, av[1]));
		init_scene(&info_mlx, av[1]);
		struct_full_status(&new_setting);//TODO: we are testing
		//free_struct(&new_setting);//TODO: implement the right free
		info_mlx.setting = &new_setting;
		debug_print_data(&info_mlx);
		debug_print_setting(&new_setting);
		manage_mlx(&info_mlx, &new_setting);
	}
	else
		return (-1 * ft_printf("%sWrong Usage:%s%s map\n", RED, RESET, av[0]));
}
