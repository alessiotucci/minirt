/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_scenes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atucci <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/04 17:02:57 by atucci            #+#    #+#             */
/*   Updated: 2024/05/11 14:59:27 by atucci           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	start_amb_light(t_setting *set, char **details)
{
	ft_printf("\t*%sSETTING UP AMBIENT LIGHTING%s**\n", YELLOW, RESET);
	set->amb_light = malloc(sizeof(t_amb_light));
	if (set->amb_light == NULL)
		return (error_msg("malloc failure\n"));
	set->amb_light->identifier = ft_strdup(details[0]);
	set->amb_light->ratio = atof(details[1]); //TODO: implement my own
	set->amb_light->color = parse_color(details[2]);
}

void	start_camera(t_setting *set, char **details)
{
	ft_printf("\n\t%s*SETTING UP CAMERA%s*\n", CYAN, RESET);

	set->camera = malloc(sizeof(t_camera));
	if (set->camera == NULL)
		return (error_msg("malloc failure\n"));
	set->camera->identifier = ft_strdup(details[0]);
	set->camera->viewpoint = parse_vector(details[1]);
	set->camera->orientation = parse_vector(details[2]);
	set->camera->fov = ft_atoi(details[3]);

}
//DOUBLE CHECK THIS ONE
void	start_lights(t_setting *set, char **details)
{
	(void)set;
	t_light	*new_light;
	new_light = malloc(sizeof(t_light));;
	if (!new_light)
		return ;//TODO add the check
	(void)new_light;
	ft_printf("\t*%sSETTING UP LIGHTS*%s\n", PURPLE, RESET);
	new_light->identifier = ft_strdup(details[0]);
	new_light->position = parse_vector(details[1]);
	new_light->brightness = atof(details[2]); //TODO: implement my own
	new_light->color = parse_color(details[3]);
	//TODO: write this function
	 add_light_to_array(new_light, set);
}
