/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atucci <atucci@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 14:18:53 by atucci            #+#    #+#             */
/*   Updated: 2024/04/28 13:40:38 by atucci           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static void	init_scene(t_mlx *info, char *mapname)
{
	info->width = DEFAULT_WIDTH;
	info->height = DEFAULT_HEIGHT;
	info->map_name = mapname;
}

//TODO: close the fd, the return of parsing_map();
int	main(int ac, char **av)
{
	t_mlx	info_mlx;

	if (ac == 2)
	{
		if (parsing_map(av[1]))
			return (-1 * ft_printf("%sWrong map: %s%s\n", RED, RESET, av[1]));
		init_scene(&info_mlx, av[1]);
		manage_mlx(&info_mlx);
	}
	else
		return (-1 * ft_printf("%sWrong Usage:%s%s map\n", RED, RESET, av[0]));
}
