/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_setting.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atucci <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/04 15:33:48 by atucci            #+#    #+#             */
/*   Updated: 2025/02/25 18:16:57 by atucci           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

//TODO:clearing up this mess
//
void	alloc_struct_elem(t_setting *setting)
{
	ft_printf("%s\tallocation%s\n", YELLOW, RESET);
	setting->lights = malloc(sizeof(t_light *) * setting->num_lights);
	if (!setting->lights)
		return ;
	setting->spheres = malloc(sizeof(t_sphere *) * setting->num_spheres);
	if (!setting->spheres)
		return ;
	setting->planes = malloc(sizeof(t_plane *) * setting->num_planes);
	if (!setting->planes)
		return ;
	setting->cylinders = malloc(sizeof(t_cylinder *) * setting->num_cylinders);
	if (!setting->cylinders)
		return ;
	ft_printf("set back %sSTRUCT%s zero again \n", YELLOW, RESET);
	setback_zero(setting);
	struct_status(setting);
}

//TODO: update this function: if in the first read I found an error, just check
//void	count_elements(char **details, t_setting *set)
int	count_elements(char **details, t_setting *set)
{
	if (my_strcmp(details[0], "L") == 0)
		set->num_lights++;
	else if (my_strcmp(details[0], "sp") == 0)
		set->num_spheres++;
	else if (my_strcmp(details[0], "pl") == 0)
		set->num_planes++;
	else if (my_strcmp(details[0], "cy") == 0)
		set->num_cylinders++;
	else if (my_strcmp(details[0], "cn") == 0)
		set->num_cones++;
	else if (my_strcmp(details[0], "A") == 0)
		set->check_amb_light++;
	else if (my_strcmp(details[0], "C") == 0)
		set->check_cam++;
	else if (my_strcmp(details[0], "\n") == 0 || my_strcmp(details[0], " ") == 0)
		;
	else
	{
		ft_printf("count_elements() ERROR!!\n");
		ft_printf("[%s%s%s]\n", RED, details[0], RESET);
		return (1);
	}
	return (0);
}

//TODO: need to be implemented
int	create_setting(char **details, t_setting *set)
{
	int	result;

	if (check_null_array(details))
	{
		ft_printf("create_setting: check null array\nreturn -1\n");
		return (-1);
	}
	if (my_strcmp(details[0], "A") == 0)
		result = start_amb_light(set, details);
	else if (my_strcmp(details[0], "C") == 0)
		result = start_camera(set, details);
	else if (my_strcmp(details[0], "L") == 0)
		result = start_lights(set, details);
	else if (my_strcmp(details[0], "sp") == 0)
		result = start_spheres(set, details);
	else if (my_strcmp(details[0], "pl") == 0)
		result = start_planes(set, details);
	else if (my_strcmp(details[0], "cy") == 0)
		result = start_cylinder(set, details);
	else
	{
		if (my_strcmp(details[0], "\n") != 0 && my_strcmp(details[0], " ") != 0)
			ft_printf("%sError: Unknown identifier '%s'%s\nreturn -1", RED, details[0], RESET);
		return (-1);
	}
	if (result != 0)
	{
		printf("create_setting: RESULT [%d]\n return -1", result);
		return (-1);
	}
	return (0);
}
