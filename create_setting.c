/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_setting.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atucci <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/04 15:33:48 by atucci            #+#    #+#             */
/*   Updated: 2024/05/05 15:47:04 by atucci           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

//TODO:clearing up this mess
void	create_setting(char **details, t_setting *set)
{

	(void)set;
	if (my_strcmp(details[0], "A") == 0)
		ft_printf("ambient lights\n");
	else if (my_strcmp(details[0], "C") == 0)
		ft_printf("cameras\n");
	else if (my_strcmp(details[0], "L") == 0)
		ft_printf("lights\n");
	else if (my_strcmp(details[0], "sp") == 0)
		ft_printf("spheres\n");
	else if (my_strcmp(details[0], "pl") == 0)
		ft_printf("planes\n");
	else if (my_strcmp(details[0], "cy") == 0)
		ft_printf("cilinders\n");
	else if (my_strcmp(details[0], "cn") == 0)
		ft_printf("cones\n");
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
/*void	create_setting(char *line, t_setting *set)
{
	char	**details;

	(void)set;
	details = ft_split(line, ' ');
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
		error_msg("not a valid identifier");
		ft_printf(details[0]);
	}
	free_string_array(details);
}*/
