/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_debug2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atucci <atucci@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 16:24:35 by atucci            #+#    #+#             */
/*   Updated: 2025/02/25 15:19:09 by atucci           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

//5
void	print_color(t_color color)
{
	printf("%sR: %lf %s", RED, color.r, RESET);
	printf("%sG: %lf %s", GREEN, color.g, RESET);
	printf("%sB: %lf%s\n", BLUE, color.b, RESET);
}

//4
void	print_camera(t_camera *camera)
{
	printf("++++++++++++Printing out the cammera stuff++++++++++++++++++++\n");
	printf("ViewPoint: ");
	print_vector(camera->viewpoint);
	printf("Orentation: ");
	print_vector(camera->orientation);
	printf("FOV:[%d]\n", camera->fov);
	printf("++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n");
	printf("ViewPoint: ");
}

//3
void	print_ambient_light(t_amb_light *amb_light)
{
	printf("Ratio of ambient lights: %f\n", amb_light->ratio);
	printf("Color of ambient lights: ");
	print_color(amb_light->color);
}

//2
/* Helper function, I will delete this later on */
void	struct_status(t_setting *set)
{
	ft_printf("\n\n------STRUCT STATUS -------\n");
	ft_printf("struct has [%d] planes \t  |\n", set->num_planes);
	ft_printf("struct has [%d] cylinders  |\n", set->num_cylinders);
	ft_printf("struct has [%d] spheres \t  |\n", set->num_spheres);
	ft_printf("struct has [%d] lights\t  |\n", set->num_lights);
	ft_printf("---------------------------\n\n");
}

//1
void	struct_full_status(t_setting *set)
{
	printf("\n\n------STRUCT %sFULL %sSTATUS -------\n", PURPLE, RESET);
	printf("\n*\t %sAMBIENT LIGHTS%s *\n", BLUE, RESET);
	print_ambient_light(set->amb_light);
	printf("\n*\t%sCAMERA STATS%s *\n", BLUE, RESET);
	print_camera(set->camera);
	printf("\n* n.[%s%d%s] PLANES \t\n", RED, set->num_planes, RESET);
	print_planes(set->num_planes, set->planes);
	printf("\n* n.[%s%d%s] CYLINDERS  |\n", RED, set->num_cylinders, RESET);
	print_cylinders(set->num_cylinders, set->cylinders);
	printf("\n* n.[%s%d%s] SPHERES \t  |\n", RED, set->num_spheres, RESET);
	print_spheres(set->num_spheres, set->spheres);
	printf("\n* n.[%s%d%s] LIGHTS\t  |\n", RED, set->num_lights, RESET);
	print_lights(set->num_lights, set->lights);
	printf("---------------------------\n\n");
}
