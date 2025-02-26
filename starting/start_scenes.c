/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_scenes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atucci <atucci@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 15:16:19 by atucci            #+#    #+#             */
/*   Updated: 2025/02/26 21:36:09 by atucci           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

/* as you can see, there is a check on the lenght of the matrix details
 * I need to add a message in other case, were the lenght isn´t right! */
//TODO: double check ratio and fov
int	start_amb_light(t_setting *set, char **details)
{
	if (validate_amb_light(details) == -1)
		return (-1);
	ft_printf("\t*%sSETTING UP AMBIENT LIGHTING%s**\n", YELLOW, RESET);
	set->amb_light = malloc(sizeof(t_amb_light));
	if (set->amb_light == NULL)
		return (error_msg("malloc failure\n"), -1);
	set->amb_light->identifier = ft_strdup(details[0]);
	set->amb_light->ratio = my_atof(details[1]);
	set->amb_light->color = parse_color(details[2], set);
	return (0);
}

int	start_camera(t_setting *set, char **details)
{
	if (validate_camera(details) == -1)
		return (-1);
	ft_printf("\n\t%s*SETTING UP CAMERA%s*\n", CYAN, RESET);
	set->camera = malloc(sizeof(t_camera));
	if (set->camera == NULL)
		return (error_msg("malloc failure\n"), -1);
	set->camera->identifier = ft_strdup(details[0]);
	set->camera->viewpoint = parse_vector(details[1], 1.0, set);
	set->camera->orientation = parse_vector(details[2], 0.0, set);
	set->camera->fov = ft_atoi(details[3]);
	set->camera->image_plane_height = 0.0;
	set->camera->image_plane_width = 0.0;
	return (0);
}

//DOUBLE CHECK THIS ONE
int	start_lights(t_setting *set, char **details)
{
	t_light	*new_light;

	if (validate_light(details) == -1)
		return (-1);
	ft_printf("\t*%sSETTING UP LIGHTS*%s\n", PURPLE, RESET);
	new_light = malloc(sizeof(t_light));
	if (new_light == NULL)
		return (free(new_light), error_msg("malloc failure\n"), -1);
	new_light->identifier = ft_strdup(details[0]);
	if (new_light->identifier == NULL)
		return (free(new_light), -1);
	new_light->position = parse_vector(details[1], 1.0, set);
	new_light->brightness = my_atof(details[2]);
	new_light->color = parse_color(details[3], set);
	add_light_to_array(new_light, set);
	return (0);
}
