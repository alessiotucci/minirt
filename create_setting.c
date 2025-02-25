/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_setting.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atucci <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/04 15:33:48 by atucci            #+#    #+#             */
/*   Updated: 2025/02/25 16:17:40 by atucci           ###   ########.fr       */
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
	else if (my_strcmp(details[0], "A") == 0 || my_strcmp(details[0], "C") == 0)
		;
	else if (my_strcmp(details[0], "\n") == 0 || my_strcmp(details[0], " ") == 0)
		;
	else
	{
		ft_printf("[%s%s%s]\n", RED, details[0], RESET);
		ft_printf("found unexpected identifier, in count elements!!\n");
		ft_printf("returning 1!\n");
		/*free_string_array(details);
		exit(EXIT_FAILURE);*/
		return (1);
	}
	return (0);
}

//TODO:
int	create_setting(char **details, t_setting *set)
//void	create_setting(char **details, t_setting *set)
{
	int	i;

	i = 0;
	if (check_null_array(details))
		return (1);;
	if (my_strcmp(details[0], "A") == 0)
		start_amb_light(set, details);
	else if (my_strcmp(details[0], "C") == 0)
		start_camera(set, details);
	else if (my_strcmp(details[0], "L") == 0)
		start_lights(set, details);
	else if (my_strcmp(details[0], "sp") == 0)
		start_spheres(set, details);
	else if (my_strcmp(details[0], "pl") == 0)
		start_planes(set, details);
	else if (my_strcmp(details[0], "cy") == 0)
		start_cylinder(set, details);
	else
	{
		if (my_strcmp(details[0], "\n") == 0 || my_strcmp(details[0], " ") == 0)
			ft_printf("[%s\\n%s]\n", RED, RESET);
		else
		{
			ft_printf("[%s%s%s]\n", RED, details[0], RESET);
			return (1 * ft_printf("found unexpected identifier, exiting the program!!\n\n"));
		}
	}
	return (i);
}
