/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atucci <atucci@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 15:39:13 by atucci            #+#    #+#             */
/*   Updated: 2024/04/27 22:25:57 by atucci           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static int	check_the_extension(char *filename, char *ext)
{
	int	i;
	int	j;

	i = ft_strlen(ext);
	j = ft_strlen(filename);
	while (i > 0)
	{
		if (ext[i] != filename[j])
			return (ft_printf("file doesn't have the '%s' extension\n", ext));
		i--;
		j--;
	}
	return (0 * ft_printf("%scorrect extension%s\n", GREEN, RESET));
}
int	parsing_map(char *map)
{
	return (check_the_extension(map, ".rt"));
}
