/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atucci <atucci@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 14:18:53 by atucci            #+#    #+#             */
/*   Updated: 2024/05/11 10:06:22 by atucci           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	error_msg(char *str)
{
	ft_printf("error\n");
	ft_printf("Minirt: %s%s%s", RED, str, RESET);
}

/* function to set the counter of object in the setting to zero */
void	starting_zero(t_setting *set)
{
		set->num_lights = 0;
		set->num_spheres = 0;
		set->num_planes = 0;
		set->num_cylinders = 0;
		set->num_cones = 0;
}
static void	init_scene(t_mlx *info, char *mapname)
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

	starting_zero(&new_setting);
	if (ac == 2)
	{
		if (parsing_map(av[1], &new_setting))
			return (-1 * ft_printf("%sWrong map: %s%s\n", RED, RESET, av[1]));
		init_scene(&info_mlx, av[1]);
		manage_mlx(&info_mlx);
	}
	else
		return (-1 * ft_printf("%sWrong Usage:%s%s map\n", RED, RESET, av[0]));
}
