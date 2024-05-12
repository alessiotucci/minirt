/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   freeing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atucci <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 19:35:20 by atucci            #+#    #+#             */
/*   Updated: 2024/05/12 11:42:29 by atucci           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include <stdio.h>

void	free_struct(t_setting *set)
{
	(void)set;
	printf("%sRemember to free all the memory%s\n", RED, RESET);
	free(set->amb_light->identifier);
	free(set->camera->identifier);
	//fee(set->light->identifier);
	free(set->amb_light);
	free(set->camera);
	//free(set->light);
}
