/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_setting.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atucci <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/04 15:33:48 by atucci            #+#    #+#             */
/*   Updated: 2024/05/11 09:19:49 by atucci           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

//TODO:clearing up this mess
//


void	count_elements(char **details, t_setting *set)
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
	else
	{
		if (my_strcmp(details[0], "\n") == 0)
		//if (details[0][0] == '\n')
			ft_printf("[%s\\n%s]\n", RED, RESET);
		else
			ft_printf("[%s%s%s]\n", RED, details[0], RESET);
		//error_msg("not a valid identifier");
	}
}

void	create_setting(char **details, t_setting *set)
{

	if (check_null_array(details))
		return ;
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
	else if (my_strcmp(details[0], "cn") == 0)
		start_cones(set, details);
	else
	{
		if (my_strcmp(details[0], "\n") == 0)
		//if (details[0][0] == '\n')
			ft_printf("[%s\\n%s]\n", RED, RESET);
		else
			ft_printf("[%s%s%s]\n", RED, details[0], RESET);
		//error_msg("not a valid identifier");
	}
}
