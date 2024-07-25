/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atucci <atucci@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 14:18:53 by atucci            #+#    #+#             */
/*   Updated: 2024/07/25 16:10:48 by atucci           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include <stdio.h>


void	init_scene(t_mlx *info, char *mapname)
{
	info->width = DEFAULT_WIDTH;
	info->height = DEFAULT_HEIGHT;
	info->map_name = mapname;
}

//TODO: close the fd, the return of parsing_map();
int	main(int ac, char **av)
{
	t_mlx		info_mlx;
	t_setting	new_setting;

	setback_zero(&new_setting);
	if (ac == 2)
	{
		if (parsing_map(av[1], &new_setting))
			return (-1 * ft_printf("%sWrong map: %s%s\n", RED, RESET, av[1]));
		init_scene(&info_mlx, av[1]);
		struct_full_status(&new_setting);//TODO: we are testing
		//free_struct(&new_setting);//TODO: implement the right free
		info_mlx.setting = &new_setting;
		manage_mlx(&info_mlx, &new_setting);
	}
	else
		return (-1 * ft_printf("%sWrong Usage:%s%s map\n", RED, RESET, av[0]));
}
