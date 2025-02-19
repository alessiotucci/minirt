/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atucci <atucci@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 14:18:53 by atucci            #+#    #+#             */
/*   Updated: 2025/02/19 10:03:06 by atucci           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include <stdio.h>

//2
int	check_the_extension(char *filename, char *ext)
{
	int	i;
	int	j;

	i = ft_strlen(ext);
	j = ft_strlen(filename);
	if (i >= j)
		return (-1 * ft_printf("%sfilename too short%s\n", RED, RESET));
	while (i > 0)
	{
		if (ext[i] != filename[j])
			return (ft_printf("file doesn't have the '%s' extension\n", ext));
		i--;
		j--;
	}
	return (0 * ft_printf("%scorrect extension%s\n", GREEN, RESET));
}

//1
int	parsing_map(char *map, t_setting *set)
{
	if (check_the_extension(map, ".rt") == 0)
		return (open_map(map, set));
	else
		return (-1);
}
void	init_scene(t_mlx *info, char *mapname)
{
	info->width = DEFAULT_WIDTH;
	info->height = DEFAULT_HEIGHT;
	info->map_name = mapname;
//	info->selected_object = NULL;
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
		manage_mlx(&info_mlx);
	}
	else
		return (-1 * ft_printf("%sWrong Usage:%s%s map\n", RED, RESET, av[0]));
}
