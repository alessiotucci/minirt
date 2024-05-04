/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_setting.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atucci <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/04 15:33:48 by atucci            #+#    #+#             */
/*   Updated: 2024/05/04 16:09:04 by atucci           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	create_setting(char *line)
{
	char	**details;

	details = ft_split(line, ' ');
	if (my_strcmp(details[0], "A") == 0)
		ft_printf("ambient lightning\n");
	else if (my_strcmp(details[0], "C") == 0)
		ft_printf("camera\n");
	else if (my_strcmp(details[0], "L") == 0)
		ft_printf("light source\n");
	else if (my_strcmp(details[0], "sp") == 0)
		ft_printf("sphere\n");
	else if (my_strcmp(details[0], "pl") == 0)
		ft_printf("plane\n");
	else if (my_strcmp(details[0], "cy") == 0)
		ft_printf("cylinder\n");
	else if (my_strcmp(details[0], "cn") == 0)
		ft_printf("cone\n");
	else
		return (error_msg("not a valid identifier"));
	free_string_array(details);
}
