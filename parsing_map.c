/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atucci <atucci@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 15:39:13 by atucci            #+#    #+#             */
/*   Updated: 2024/04/28 13:45:31 by atucci           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static int	check_the_extension(char *filename, char *ext)
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

int	open_map(char *filename)
{
	int	fd;

	fd = open(filename, O_RDONLY);
	if (fd == -1)
		return (ft_printf("%sError map: %s%s\n", RED, filename, RESET));
	else
		return (close(fd), 0);
	
}

int	parsing_map(char *map)
{
	if (check_the_extension(map, ".rt") == 0)
		return (open_map(map));
	else
		return (-1);
}
